#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "ray.hpp"
#include "color.hpp"
#include "hittable.hpp"

class Material {
public:
  virtual ~Material() = default;

  virtual bool Scatter(const Ray &ray_in, const HitRecord &record,
                       Color &attenuation, Ray &scattered) const {
    return false;
  }
};

#endif
