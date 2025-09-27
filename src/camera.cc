#include "camera.hpp"
#include "color.hpp"
#include "common.hpp"
#include "hittable.hpp"
#include "vec3.hpp"

void Camera::Initialize() {
    image_h_ = int(image_w_ / aspect_ratio_);
    image_h_ = (image_h_ < 1) ? 1 : image_h_;

    pixel_samples_scale_ = 1.0 / samples_per_pixel_;
    center_ = point3(0, 0, 0);

    auto focal_length = 1.0;
    auto viewport_h = 2.0;
    auto viewport_w = viewport_h * (double(Camera::image_w_) / Camera::image_h_);

    // Calculate the vectors across the horizontal and down the vertical
    // Negative since due to RHS coordinate system
    auto viewport_u = vec3(viewport_w, 0, 0);
    auto viewport_v = vec3(0, -viewport_h, 0);

    pixel_delta_u_ = viewport_u / Camera::image_w_;
    pixel_delta_v_ = viewport_v / Camera::image_h_;

    vec3 P = vec3(0, 0, focal_length);
    auto viewport_upper_left = Camera::center_ - P - (viewport_u / 2) - (viewport_v / 2);
    pixel00_loc_ = viewport_upper_left + 0.5 * (Camera::pixel_delta_u_ + Camera::pixel_delta_v_);
}

vec3 Camera::SampleSquare() const {
    // Returns a vector to a random point in the square [-0.5, 0.5) x [-0.5, 0.5) x 0
    return vec3(random_double() - 0.5, random_double() - 0.5, 0);
}

ray Camera::GetRay(int i, int j) const {
    auto offset = SampleSquare();
    auto xComponent = (i + offset.x()) * Camera::pixel_delta_u_;
    auto yComponent = (j + offset.y()) * Camera::pixel_delta_v_;
    auto pixel_sample = Camera::pixel00_loc_ + xComponent + yComponent;
    auto ray_origin = Camera::center_;
    auto ray_direction = pixel_sample - ray_origin;

    return ray(ray_origin, ray_direction);
}

color Camera::RayColor(const ray &r, int depth, const Hittable &world) const {
    // Using linear interpolation (lerp) to blend colors
    // blendedValue = (1-a) * startValue + (a * endValue);
    if (depth <= 0) {
        return color(0, 0, 0);
    }

    HitRecord rec;

    if (world.Hit(r, interval(0.001, infinity), rec)) {
        vec3 direction = rec.normal_ + random_unit_vector();
        return 0.5 * RayColor(ray(rec.p_, direction), depth - 1, world);
    }

    vec3 unit_dir = unit(r.direction());
    auto a = 0.5 * (unit_dir.y() + 1.0);

    // Skybox
    const color light_blue = color(0.529, 0.808, 0.922);
    const color deep_blue = color(0.118, 0.565, 0.898);

    return (1.0 - a) * deep_blue + a * light_blue;
}

void Camera::Render(const Hittable &world) {
    Camera::Initialize();

    std::clog << "Rendering begun." << "\n";

    std::cout << "P3\n" << Camera::image_w_ << " " << Camera::image_h_ << "\n255\n";
    for (int j = 0; j < Camera::image_h_; j++) {
        std::clog << "\rScanlines remaining: " << (Camera::image_h_ - j) << ' ' << std::flush;

        for (int i = 0; i < Camera::image_w_; i++) {
            color pixel(0, 0, 0);

            for (int sample = 0; sample < Camera::samples_per_pixel_; sample++) {
                ray r = Camera::GetRay(i, j);
                pixel += RayColor(r, Camera::max_depth_, world);
            }

            write_color(std::cout, Camera::pixel_samples_scale_ * pixel);
        }
    }

    std::string spaces(50, ' ');
    std::clog << "\r" << "Done." << spaces << "\n";
}
