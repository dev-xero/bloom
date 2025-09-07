#include "color.h"
#include "common.h"
#include "hittable_list.h"
#include "ray.h"
#include "sphere.h"
#include "vec3.h"

int main() {
    // ===================================================
    // Image
    // ===================================================
    auto aspect_ratio = 16.0 / 9.0;
    int image_w = 400;

    // ===================================================
    // Calculate the image height, must be atleast 1
    // ===================================================
    int image_h = int(image_w / aspect_ratio);
    image_h = (image_h < 1) ? 1 : image_h;

    // ===================================================
    // World
    // ===================================================
    hittable_list world;
    world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
    world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));
    std::clog << "World has " << world.objects.size() << " objects\n";

    // ===================================================
    // Camera setup
    // ===================================================
    auto focal_length = 1.0;
    auto viewport_h = 2.0;
    // we're not using aspect ratio due to height condition
    auto viewport_w = viewport_h * (double(image_w) / image_h);
    auto camera_center = point3(0, 0, 0);

    // ===================================================
    // Calculate the vectors across the horizontal and
    // down the vertical viewport edges
    // ===================================================
    auto viewport_u = vec3(viewport_w, 0, 0);
    // negative since it's the opposite direction
    auto viewport_v = vec3(0, -viewport_h, 0);

    // ===================================================
    // Calculate the horizontal and vertical delta vectors
    // ===================================================
    auto pixel_du = viewport_u / image_w;
    auto pixel_dv = viewport_v / image_h;

    // ===================================================
    // Calculate the position of the upper left pixel
    // ===================================================
    auto view_upper_left =
        camera_center - vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
    auto pixel00_loc = view_upper_left + 0.5 * (pixel_du + pixel_dv);

    // ===================================================
    // Render PPM
    // ===================================================
    std::cout << "P3\n" << image_w << " " << image_h << "\n255\n";

    for (int j = 0; j < image_h; j++) {
        std::clog << "\rScanlines remaining: " << (image_h - j) << ' ' << std::flush;

        for (int i = 0; i < image_w; i++) {
            auto pixel_center = pixel00_loc + (i * pixel_du) + (j * pixel_dv);
            auto ray_direction = pixel_center - camera_center;
            // setup ray and colors
            ray r(camera_center, ray_direction);
            color pixel_color = ray_color(r, world);

            write_color(std::cout, pixel_color);
        }

        std::string spaces(50, ' ');
        std::clog << "\r" << "Done." << spaces << "\n";
    }
}
