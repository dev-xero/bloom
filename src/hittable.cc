#include "hittable.hpp"
#include "ray.hpp"
#include "vec3.hpp"

void HitRecord::SetFaceNormal(const Ray &r, const Vec3 &outward_normal) {
    // Sets the hit record normal vector
    // NOTE: the parameter `outward_normal` is assumed to have unit length
    HitRecord::front_face_ = Dot(r.Direction(), outward_normal) < 0;
    HitRecord::normal_ = front_face_ ? outward_normal : -outward_normal;
}
