#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "color.hpp"
#include "hittable.hpp"

class Material {
  public:
    virtual ~Material() = default;

    virtual bool Scatter(const ray &ray_in, const HitRecord &record, color &attenuation,
                         ray &scattered) const {
        return false;
    }
};

#endif
