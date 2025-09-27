#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "hittable.hpp"
#include "interval.hpp"
#include "ray.hpp"
#include "vec3.hpp"

class Sphere : public Hittable {
  public:
    Sphere(const point3 &center, double radius) : center_(center), radius_(std::fmax(0, radius)) {
        // TODO: Initialize the material pointer `mat_`
    }

    bool Hit(const ray &r, interval ray_t, HitRecord &rec) const override;

  private:
    point3 center_;
    double radius_;
    shared_ptr<Material> mat_;
};

#endif
