#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "hittable.hpp"
#include "interval.hpp"
#include "ray.hpp"
#include "vec3.hpp"

class sphere : public hittable {
  public:
    sphere(const point3 &center, double radius) : center(center), radius(std::fmax(0, radius)) {}

    bool hit(const ray &r, interval ray_t, hit_record &rec) const override;

  private:
    const point3 center;
    double radius;
};

#endif
