#ifndef COLOR_HPP
#define COLOR_HPP

#include "hittable.hpp"
#include "ray.hpp"
#include "vec3.hpp"

#include <iostream>

using color = vec3;

void write_color(std::ostream &out, const color &pixel_color);
double linear_to_gamma(double linear_component);
color ray_color(const ray &r, const hittable &world);

#endif
