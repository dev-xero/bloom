#include "color.h"
#include "common.h"
#include "hittable.h"
#include "hittable_list.h"
#include "ray.h"
#include "sphere.h"
#include "vec3.h"

int main() {
    // Image
    auto aspect_ratio = 16.0 / 9.0;
    int image_w = 400;

    // Calculate the image height, and ensure it's atleast 1
    int image_h = int(image_w / aspect_ratio);
    image_h = (image_h < 1) ? 1 : image_h;

    // Camera setup
    auto focal_length = 1.0;
    auto viewport_h = 2.0;
    auto viewport_w =
        viewport_h *
        (double(image_w) / image_h); // we're not using aspect ratio due to height condition
    auto camera_center = point3(0, 0, 0);

    // Calculate the vectors across the horizontal and down the vertical viewport edges
    auto viewport_u = vec3(viewport_w, 0, 0);
    auto viewport_v = vec3(0, -viewport_h, 0); // negative since it's the opposite direction

    // Calculate the horizontal and vertical delta vectors
    auto pixel_delta_u = viewport_u / image_w;
    auto pixel_delta_v = viewport_v / image_h;

    // Calculate the position of the upper left pixel
    auto viewport_upper_left =
        camera_center - vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
    auto pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    // Render PPM
    std::cout << "P3\n" << image_w << " " << image_h << "\n255\n";

    for (int j = 0; j < image_h; j++) {
        std::clog << "\rScanlines remaining: " << (image_h - j) << ' ' << std::flush;

        for (int i = 0; i < image_w; i++) {
            auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
            auto ray_direction = pixel_center - camera_center;

            ray r(camera_center, ray_direction);

            color pixel_color = ray_color(r);
            write_color(std::cout, pixel_color);
        }

        std::string spaces(50, ' ');
        std::clog << "\r" << "Done." << spaces << "\n";
    }
}
