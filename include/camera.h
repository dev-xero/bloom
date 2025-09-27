#ifndef CAMERA_H
#define CAMERA_H

#include "color.h"
#include "hittable.h"
#include "vec3.h"

class camera {
  public:
    double aspect_ratio = 1.0;
    int image_w = 100;
    int samples_per_pixel = 10;
    int max_depth = 10;

    void render(const hittable &world);

  private:
    int image_h;
    double pixel_samples_scale;
    point3 center;
    point3 pixel00_loc;
    vec3 pixel_delta_u;
    vec3 pixel_delta_v;

    void initialize();
    ray get_ray(int i, int j) const;
    vec3 sample_square() const;
    color ray_color(const ray &r, int depth, const hittable &world) const;
};

#endif
