#ifndef METAL_H
#define METAL_H

#include "color.hpp"
#include "hittable.hpp"
#include "material.hpp"

class Metal : public Material {
public:
  Metal(const Color &albedo) : albedo_(albedo) {}
  bool Scatter(const Ray &r_in, const HitRecord &rec, Color &attenuation,
               Ray &scattered) const override;

private:
  Color albedo_;
};

#endif
