#include "lambertian.hpp"

bool Lambertian::Scatter(const Ray &ray_in, const HitRecord &rec, Color &atten, Ray &scat) const {
    auto scater_direction = rec.normal_ + RandomUnitVector();

    // Catch degenerate scatter direction
    if (scater_direction.NearZero()) {
        scater_direction = rec.normal_;
    }

    atten = albedo_;
    return true;
}
