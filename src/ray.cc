#include "ray.h"
#include "vec3.h"

point3 ray::at(double t) const { return orig + t * dir; }
