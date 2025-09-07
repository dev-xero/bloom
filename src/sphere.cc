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
    // Optimization:
    // recall that a vector dotted with itself is equal to the squared
    // length of that vector, secondly setting b = -2h, we get:
    // 2h + 2(root(h^2 - ac)) / 2a
    // h + root(h^2 - ac) / a
    // b = -2d.(C-Q), and b = -2h, hence:
    // h = b/-2 = d.(C-Q)
    vec3 oc = center - r.origin();
    auto a = r.direction().length_squared();
    auto h = dot(r.direction(), oc);
    auto c = oc.length_squared() - radius * radius;
    auto discriminant = h * h - a * c;

    if (discriminant < 0) {
        return -1.0;
    } else {
        // since the ray can hit the sphere at two points (entry and exit)
        // we want the closer of the two given by:
        // t1 = (-b - root(D)) / 2a
        // after the optimization: we can use h instead
        return (h - std::sqrt(discriminant)) / a;
    }
}
