#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "color.hpp"
#include "hittable.hpp"
#include "vec3.hpp"

class Camera {
  public:
    double aspect_ratio_ = 1.0;
    int image_w_ = 100;
    int samples_per_pixel_ = 10;
    int max_depth_ = 10;

    void Render(const Hittable &world);

  private:
    int image_h_;
    double pixel_samples_scale_;
    point3 center_;
    point3 pixel00_loc_;
    vec3 pixel_delta_u_;
    vec3 pixel_delta_v_;

    void Initialize();
    vec3 SampleSquare() const;
    ray GetRay(int i, int j) const;
    color RayColor(const ray &r, int depth, const Hittable &world) const;
};

#endif
