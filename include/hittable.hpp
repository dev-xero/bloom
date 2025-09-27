#ifndef HITTABLE_HPP
#define HITTABLE_HPP

#include "interval.hpp"
#include "ray.hpp"
#include "vec3.hpp"

class hit_record {
  public:
    point3 p;
    vec3 normal;
    double t;
    bool front_face;

    void set_face_normal(const ray &r, const vec3 &outward_normal);
};

class hittable {
  public:
    virtual ~hittable() = default;
    virtual bool hit(const ray &r, interval ray_t, hit_record &rec) const = 0;
};

#endif
