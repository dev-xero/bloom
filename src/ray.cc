#include "ray.h"

point3 ray::at(double t) const { return orig + t * dir; }
