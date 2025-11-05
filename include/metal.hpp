#ifndef METAL_H
#define METAL_H

#include "color.hpp"
#include "hittable.hpp"
#include "material.hpp"
#include "ray.hpp"

class Metal : public Material {
  public:
    Metal(const Color &albedo, double fuzz) : albedo_(albedo), fuzz(fuzz < 1 ? fuzz : 1) {}
    bool Scatter(const Ray &r_in, const HitRecord &rec, Color &attenuation, Ray &scattered) const override;

  private:
    Color albedo_;
    double fuzz;
};

#endif
