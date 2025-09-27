#include "ray.hpp"
#include "vec3.hpp"

point3 ray::at(double t) const { return orig + t * dir; }
