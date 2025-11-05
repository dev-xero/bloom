#ifndef SPHERE_HPP
#define SPHERE_HPP

#include <cmath>

#include "common.hpp"
#include "hittable.hpp"
#include "interval.hpp"
#include "ray.hpp"
#include "vec3.hpp"

class Sphere : public Hittable {
  public:
    Sphere(const Point3 &center, double radius, shared_ptr<Material> mat)
        : center_(center), radius_(std::fmax(0, radius)), mat_(mat) {}

    bool Hit(const Ray &r, Interval ray_t, HitRecord &rec) const override;

  private:
    Point3 center_;
    double radius_;
    shared_ptr<Material> mat_;
};

#endif
