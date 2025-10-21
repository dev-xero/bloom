#include "lambertian.hpp"

bool Lambertian::Scatter(const Ray &ray_in, const HitRecord &rec, Color &attenuation,
                         Ray &scattered) const {
    auto scatter_direction = rec.normal_ + RandomUnitVector();
    // Catch degenerate scatter direction
    if (scatter_direction.NearZero()) {
        scatter_direction = rec.normal_;
    }
    scattered = Ray(rec.p_, scatter_direction);
    attenuation = Lambertian::albedo_;
    return true;
}
