#ifndef HITTABLE_HPP
#define HITTABLE_HPP

#include "common.hpp"
#include "interval.hpp"
#include "ray.hpp"
#include "vec3.hpp"

class Material;

class HitRecord {
  public:
    Point3 p_;
    Vec3 normal_;
    shared_ptr<Material> mat_;
    double t_;
    bool front_face_;

    void SetFaceNormal(const Ray &r, const Vec3 &outward_normal);
};

class Hittable {
  public:
    virtual ~Hittable() = default;
    virtual bool Hit(const Ray &r, Interval ray_t, HitRecord &rec) const = 0;
};

#endif
