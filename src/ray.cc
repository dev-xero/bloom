#include "ray.h"
#include "vec3.h"

point3 ray::at(double t) const { return ray::orig + t * ray::dir; }
