#include "hittable.hpp"

void HitRecord::SetFaceNormal(const ray &r, const vec3 &outward_normal) {
    // Sets the hit record normal vector
    // NOTE: the parameter `outward_normal` is assumed to have unit length
    HitRecord::front_face_ = dot(r.direction(), outward_normal) < 0;
    HitRecord::normal_ = front_face_ ? outward_normal : -outward_normal;
}
