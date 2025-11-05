#include <iostream>
#include <string>

#include "camera.hpp"
#include "color.hpp"
#include "common.hpp"
#include "hittable.hpp"
#include "interval.hpp"
#include "material.hpp" // forward declaration purposes
#include "ray.hpp"
#include "vec3.hpp"

void Camera::Initialize() {
    image_h_ = int(image_w_ / aspect_ratio_);
    image_h_ = (image_h_ < 1) ? 1 : image_h_;

    pixel_samples_scale_ = 1.0 / samples_per_pixel_;
    center_ = Point3(0, 0, 0);

    auto focal_length = 1.0;
    auto viewport_h = 2.0;
    auto viewport_w = viewport_h * (double(Camera::image_w_) / Camera::image_h_);

    // Calculate the vectors across the horizontal and down the vertical
    // Negative since due to RHS coordinate system
    auto viewport_u = Vec3(viewport_w, 0, 0);
    auto viewport_v = Vec3(0, -viewport_h, 0);

    pixel_delta_u_ = viewport_u / Camera::image_w_;
    pixel_delta_v_ = viewport_v / Camera::image_h_;

    Vec3 P = Vec3(0, 0, focal_length);
    auto viewport_upper_left = Camera::center_ - P - (viewport_u / 2) - (viewport_v / 2);
    pixel00_loc_ = viewport_upper_left + 0.5 * (Camera::pixel_delta_u_ + Camera::pixel_delta_v_);
}

Vec3 Camera::SampleSquare() const {
    // Returns a vector to a random point in the square.
    // [-0.5, 0.5) x [-0.5, 0.5) x 0
    return Vec3(RandomDouble() - 0.5, RandomDouble() - 0.5, 0);
}

Ray Camera::GetRay(int i, int j) const {
    auto offset = SampleSquare();

    auto xComponent = (i + offset.x()) * Camera::pixel_delta_u_;
    auto yComponent = (j + offset.y()) * Camera::pixel_delta_v_;

    auto pixel_sample = Camera::pixel00_loc_ + xComponent + yComponent;

    auto ray_origin = Camera::center_;
    auto ray_direction = pixel_sample - ray_origin;

    return Ray(ray_origin, ray_direction);
}

Color Camera::RayColor(const Ray &r, int depth, const Hittable &world) const {
    // If we've exceeded the ray bounce limit, no more light is gathered.
    if (depth <= 0) {
        return Color(0, 0, 0);
    }

    HitRecord rec;

    // Collision Detection
    if (world.Hit(r, Interval(0.001, infinity), rec)) {
        Ray scattered;
        Color attenuation;
        if (rec.mat_->Scatter(r, rec, attenuation, scattered)) {
            return attenuation * RayColor(scattered, depth - 1, world);
        }
        return Color(0, 0, 0);
    }

    Vec3 unit_dir = Unit(r.Direction());
    auto a = 0.5 * (unit_dir.y() + 1.0);

    // SkyBox - linear interpolation
    // blendedValue = (1-a) * startValue + (a * endValue);
    const Color light_blue = Color(0.529, 0.808, 0.922);
    const Color deep_blue = Color(0.118, 0.565, 0.898);

    return (1.0 - a) * deep_blue + a * light_blue;
}

void Camera::Render(const Hittable &world) {
    Camera::Initialize();

    std::clog << "Rendering begun." << "\n";
    std::cout << "P3\n" << Camera::image_w_ << " " << Camera::image_h_ << "\n255\n";

    for (int j = 0; j < Camera::image_h_; j++) {
        std::clog << "\rScans remaining: " << (Camera::image_h_ - j) << ' ' << std::flush;
        for (int i = 0; i < Camera::image_w_; i++) {
            Color pixel(0, 0, 0);
            for (int sample = 0; sample < Camera::samples_per_pixel_; sample++) {
                Ray r = Camera::GetRay(i, j);
                pixel += RayColor(r, Camera::max_depth_, world);
            }
            color::WriteColor(std::cout, Camera::pixel_samples_scale_ * pixel);
        }
    }

    std::string spaces(50, ' ');
    std::clog << "\r" << "Done." << spaces << "\n";
}
