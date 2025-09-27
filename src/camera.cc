#include "camera.h"
#include "color.h"
#include "common.h"
#include "hittable.h"
#include "vec3.h"

// ==============================================================
// Initialize
// ==============================================================
void camera::initialize() {
    image_h = int(image_w / aspect_ratio);
    image_h = (image_h < 1) ? 1 : image_h;

    pixel_samples_scale = 1.0 / samples_per_pixel;

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
// Get Ray
// ==============================================================
ray camera::get_ray(int i, int j) const {
    auto offset = sample_square();
    auto pixel_sample =
        pixel00_loc + ((i + offset.x()) * pixel_delta_u) + ((j + offset.y()) * pixel_delta_v);
    auto ray_origin = center;
    auto ray_direction = pixel_sample - ray_origin;

    return ray(ray_origin, ray_direction);
}

// ==============================================================
// Sample Square
// ==============================================================
vec3 camera::sample_square() const {
    // Returns the vector to a random point in the [-.5,-.5]-[+.5,+.5]
    // unit square
    return vec3(random_double() - 0.5, random_double() - 0.5, 0);
}

// ==============================================================
// Ray Color
// ==============================================================
// Using linear interpolation (lerp) to blend colors
// blendedValue = (1-a) * startValue + (a * endValue);
// ==============================================================
color camera::ray_color(const ray &r, int depth, const hittable &world) const {
    if (depth <= 0) {
        return color(0, 0, 0);
    }

    hit_record rec;

    if (world.hit(r, interval(0.001, infinity), rec)) {
        vec3 direction = rec.normal + random_unit_vector();
        return 0.5 * ray_color(ray(rec.p, direction), depth - 1, world);
    }

    vec3 unit_dir = unit(r.direction());
    auto a = 0.5 * (unit_dir.y() + 1.0);

    const color light_blue = color(0.529, 0.808, 0.922);
    const color deep_blue = color(0.118, 0.565, 0.898);

    return (1.0 - a) * deep_blue + a * light_blue;
}

// ==============================================================
// Render
// ==============================================================
void camera::render(const hittable &world) {
    camera::initialize();

    std::clog << "Rendering begun." << "\n";

    std::cout << "P3\n" << image_w << " " << image_h << "\n255\n";

    for (int j = 0; j < image_h; j++) {
        std::clog << "\rScanlines remaining: " << (image_h - j) << ' ' << std::flush;
        for (int i = 0; i < image_w; i++) {
            color pixel(0, 0, 0);
            // sampled rendering
            for (int sample = 0; sample < samples_per_pixel; sample++) {
                ray r = get_ray(i, j);
                pixel += ray_color(r, max_depth, world);
            }
            write_color(std::cout, pixel_samples_scale * pixel);
        }
    }

    std::string spaces(50, ' ');
    std::clog << "\r" << "Done." << spaces << "\n";
}
