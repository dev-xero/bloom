#ifndef HITTABLE_LIST_HPP
#define HITTABLE_LIST_HPP

#include <vector>

#include "ray.hpp"
#include "common.hpp"
#include "hittable.hpp"
#include "interval.hpp"

class Hittable_list : public Hittable {
  public:
    std::vector<shared_ptr<Hittable>> objects_;

    Hittable_list() {}
    Hittable_list(shared_ptr<Hittable> object) { Add(object); }

    void Clear() { objects_.clear(); }
    void Add(shared_ptr<Hittable> object) { objects_.push_back(object); }

    bool Hit(const Ray &r, Interval ray_t, HitRecord &rec) const override;
};

#endif
