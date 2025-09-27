#include "hittable.hpp"

void hit_record::set_face_normal(const ray &r, const vec3 &outward_normal) {
    // Sets the hit record normal vector
    // NOTE: the parameter `outward_normal` is assumed to have unit length
    hit_record::front_face = dot(r.direction(), outward_normal) < 0;
    hit_record::normal = front_face ? outward_normal : -outward_normal;
}
