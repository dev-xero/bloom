#ifndef COLOR_HPP
#define COLOR_HPP

#include "hittable.hpp"
#include "ray.hpp"
#include "vec3.hpp"

#include <iostream>

using Color = Vec3;

namespace color {

void WriteColor(std::ostream &out, const Color &pixel_color);

double LinearToGamma(double linear_component);

Color RayColor(const Ray &r, const Hittable &world);

} // namespace color

#endif
