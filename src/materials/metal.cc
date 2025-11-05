#include "metal.hpp"
#include "color.hpp"
#include "hittable.hpp"
#include "ray.hpp"
#include "vec3.hpp"

bool Metal::Scatter(const Ray &r_in, const HitRecord &rec, Color &attenuation, Ray &scattered) const {
    Vec3 reflected = Reflect(r_in.Direction(), rec.normal_);
    scattered = Ray(rec.p_, reflected);
    attenuation = Metal::albedo_;
    return true;
}
