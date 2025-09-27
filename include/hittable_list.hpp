#ifndef HITTABLE_LIST_HPP
#define HITTABLE_LIST_HPP

#include "common.hpp"
#include "hittable.hpp"
#include "interval.hpp"
#include <vector>

class hittable_list : public Hittable {
  public:
    std::vector<shared_ptr<Hittable>> objects;

    hittable_list() {}
    hittable_list(shared_ptr<Hittable> object) { add(object); }

    void clear() { objects.clear(); }
    void add(shared_ptr<Hittable> object) { objects.push_back(object); }

    bool Hit(const ray &r, interval ray_t, HitRecord &rec) const override;
};

#endif
