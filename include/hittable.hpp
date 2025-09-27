#ifndef HITTABLE_HPP
#define HITTABLE_HPP

#include "interval.hpp"
#include "ray.hpp"
#include "vec3.hpp"

class Material;

class HitRecord {
  public:
    point3 p_;
    vec3 normal_;
    shared_ptr<Material> mat_;
    double t_;
    bool front_face_;

    void SetFaceNormal(const ray &r, const vec3 &outward_normal);
};

class Hittable {
  public:
    virtual ~Hittable() = default;
    virtual bool Hit(const ray &r, interval ray_t, HitRecord &rec) const = 0;
};

#endif
