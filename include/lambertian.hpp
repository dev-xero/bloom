#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H

#include "color.hpp"
#include "hittable.hpp"
#include "material.hpp"
#include "ray.hpp"
#include "vec3.hpp"

class Lambertian : public Material {
  public:
    Lambertian(const Color &albedo) : albedo_(albedo) {}

    bool Scatter(const Ray &ray_in, const HitRecord &rec, Color &atten, Ray &scat) const override;

  private:
    Color albedo_;
};

#endif
