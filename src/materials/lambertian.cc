#include "lambertian.hpp"

bool Lambertian::Scatter(const Ray &ray_in, const HitRecord &rec, Color &atten, Ray &scat) const {
    auto scatter_direction = rec.normal_ + RandomUnitVector();
    // Catch degenerate scatter direction
    if (scatter_direction.NearZero()) {
        scatter_direction = rec.normal_;
    }
    atten = Lambertian::albedo_;
    return true;
}
