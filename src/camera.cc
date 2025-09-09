#include "camera.h"
#include "color.h"
#include "hittable.h"

// ==============================================================
// Initialize
// ==============================================================
void camera::initialize() {
    image_h = int(image_w / aspect_ratio);
    image_h = (image_h < 1) ? 1 : image_h;

    center = point3(0, 0, 0);

    // Determine viewport dimensions
    auto focal_length = 1.0;
    auto viewport_h = 2.0;
    auto viewport_w = viewport_h * (double(image_w) / image_h);

    // Calculate the vectors across the horizontal
    // and down the vertical
    auto viewport_u = vec3(viewport_w, 0, 0);
    // Negative since due to RHS coordinate system
    auto viewport_v = vec3(0, -viewport_h, 0);

    // Calculate the horizontal and vertical deltas
    pixel_delta_u = viewport_u / image_w;
    pixel_delta_v = viewport_v / image_h;

    // Calculate the location of the upper left pixel
    vec3 P = vec3(0, 0, focal_length);
    auto viewport_upper_left = center - P - (viewport_u / 2) - (viewport_v / 2);
    pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
}

// ==============================================================
// Ray Color
// ==============================================================
// Using linear interpolation (lerp) to blend colors
// blendedValue = (1-a) * startValue + (a * endValue);
// ==============================================================
color camera::ray_color(const ray &r, const hittable &world) const {
    hit_record rec;
    if (world.hit(r, interval(0, infinity), rec)) {
        return 0.5 * (rec.normal + color(1, 1, 1));
    }

    vec3 unit_dir = unit(r.direction());
    auto a = 0.5 * (unit_dir.y() + 1.0);

    const color pink = color(1, 0.847, 0.929);
    const color violet = color(0.733, 0.772, 0.976);

    return (1.0 - a) * violet + a * pink;
}

// ==============================================================
// Render
// ==============================================================
void camera::render(const hittable &world) {
    camera::initialize();

    std::clog << "Begin Rendering." << "\n";

    // PPM image format headers
    std::cout << "P3\n" << image_w << " " << image_h << "\n255\n";

    // Write rays pixel by pixel
    for (int j = 0; j < image_h; j++) {
        std::clog << "\rScanlines remaining: " << (image_h - j) << ' ' << std::flush;

        for (int i = 0; i < image_w; i++) {
            auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
            auto ray_direction = pixel_center - center;

            ray r(center, ray_direction);
            color pixel = ray_color(r, world);

            write_color(std::cout, pixel);
        }
    }

    std::string spaces(50, ' ');
    std::clog << "\r" << "Done." << spaces << "\n";
}
