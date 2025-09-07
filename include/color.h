#ifndef COLOR_H
#define COLOR_H

#include "hittable.h"
#include "ray.h"
#include "vec3.h"

#include <iostream>

using color = vec3;

void write_color(std::ostream &out, const color &pixel_color);
color ray_color(const ray &r, const hittable &world);

#endif
