#include "sphere.hpp"

// Using vector algebra and formula of a sphere, determine whether a ray hits the sphere
//
// (C-P).(C-P) = r^2
// given P = Q + td,
// (-td + (C-Q)).(-td + (C-Q)) = r^2
//
// using vector algebra:
// t^2d.d - 2td.(C-Q) + (C-Q).(C-Q) - r^2 = 0
//
// this is a quadratic equation solvable through the discriminant formula
// if D > 0, we have 2 real solutions
bool Sphere::Hit(const ray &r, interval ray_t, HitRecord &rec) const {
    // Optimization:
    // Recall that a vector dotted with itself is equal to the squared
    // length of that vector, secondly setting b = -2h, we get:
    //
    // 2h + 2(root(h^2 - ac)) / 2a
    // h + root(h^2 - ac) / a
    // b = -2d.(C-Q), and b = -2h, hence:
    // h = b/-2 = d.(C-Q)
    vec3 oc = center_ - r.origin();
    auto a = r.direction().length_squared();
    auto h = dot(r.direction(), oc);
    auto c = oc.length_squared() - radius_ * radius_;

    auto discriminant = h * h - a * c;
    if (discriminant < 0) {
        return false;
    }

    auto sqrtd = std::sqrt(discriminant);

    // We need to find the nearest root within accepted range
    auto root = (h - sqrtd) / a;
    if (!ray_t.surrounds(root)) {
        root = (h + sqrtd) / a;
        if (!ray_t.surrounds(root)) {
            return false;
        }
    }

    rec.t_ = root;
    rec.p_ = r.at(rec.t_);

    vec3 outward_normal = (rec.p_ - center_) / radius_;
    rec.SetFaceNormal(r, outward_normal);

    return true;
}
