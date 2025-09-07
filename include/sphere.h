#ifndef SPHERE_H
#define SPHERE_H

#include "ray.h"
#include "vec3.h"

double hit_sphere(const point3 &center, double radius, const ray &r);

#endif
