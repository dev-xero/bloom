#include "hittable_list.hpp"

bool Hittable_list::Hit(const Ray &r, Interval ray_t, HitRecord &rec) const {
    HitRecord temp_rec;
    bool hit_anything = false;
    auto closest_so_far = ray_t.max_;

    for (const auto object : objects_) {
        if (object->Hit(r, Interval(ray_t.min_, closest_so_far), temp_rec)) {
            hit_anything = true;
            closest_so_far = temp_rec.t_;
            rec = temp_rec;
        }
    }

    return hit_anything;
}
