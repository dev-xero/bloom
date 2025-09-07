#include "sphere.h"

// Using vector algebra and formula of a sphere, determine
// whether a ray hits the sphere
// (C-P).(C-P) = r^2
// given P = Q + td,
// (-td + (C-Q)).(-td + (C-Q)) = r^2
// applying vector algebra,
// t^2d.d - 2td.(C-Q) + (C-Q).(C-Q) - r^2 = 0
// this is a quadratic equation solvable through the discriminant formula
// if D > 0, we have 2 real solutions
double hit_sphere(const point3 &center, double radius, const ray &r) {
    vec3 oc = center - r.origin();
    auto a = dot(r.direction(), r.direction());
    auto b = -2.0 * dot(r.direction(), oc);
    auto c = dot(oc, oc) - radius * radius;
    auto discriminant = b * b - 4 * a * c;

    if (discriminant < 0) {
        return -1.0;
    } else {
        // since the ray can hit the sphere at two points (entry and exit)
        // we want the closer of the two given by:
        // t1 = (-b - root(D)) / 2a
        return (-b - std::sqrt(discriminant)) / (2.0 * a);
    }
}
