#include "cube.h"
#include "hittable.h"
#include "interval.h"
#include <utility>

#include <bits/stdc++.h>

bool cube::hit(const ray &r, interval ray_t, hit_record &rec) const {
    // Ray-AABB intersection using slab method

    // t_x bounds
    double t_min_x = (box_min.x() - r.origin().x()) / r.direction().x();
    double t_max_x = (box_max.x() - r.origin().x()) / r.direction().x();
    if (t_min_x > t_max_x) {
        std::swap(t_min_x, t_max_x);
    }

    // t_y bounds
    double t_min_y = (box_min.y() - r.origin().y()) / r.direction().y();
    double t_max_y = (box_max.y() - r.origin().y()) / r.direction().y();
    if (t_min_y > t_max_y) {
        std::swap(t_min_y, t_max_y);
    }

    // t_z bounds
    double t_min_z = (box_min.z() - r.origin().z()) / r.direction().z();
    double t_max_z = (box_max.z() - r.origin().z()) / r.direction().z();
    if (t_min_z > t_max_z) {
        std::swap(t_min_z, t_max_z);
    }

    double t_enter = std::max({t_min_x, t_min_y, t_min_z});
    double t_exit = std::min({t_max_x, t_max_y, t_max_z});

    // invalid
    double t_min = ray_t.min;
    double t_max = ray_t.max;
    if (t_enter > t_exit || t_exit < t_min || t_enter > t_max) {
        return false;
    }

    double t = (t_enter > t_min) ? t_enter : t_exit;
    if (t < t_min || t > t_max) {
        return false;
    }

    rec.t = t;
    rec.p = r.at(t);
    rec.mat_ptr = mat_ptr;

    return true;
}
