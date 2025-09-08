#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "common.h"
#include "hittable.h"
#include "interval.h"
#include <vector>

class hittable_list : public hittable {
  public:
    std::vector<shared_ptr<hittable>> objects;

    hittable_list() {}
    hittable_list(shared_ptr<hittable> object) { add(object); }

    void clear() { objects.clear(); }
    void add(shared_ptr<hittable> object) { objects.push_back(object); }

    bool hit(const ray &r, interval ray_t, hit_record &rec) const override;
};

#endif
