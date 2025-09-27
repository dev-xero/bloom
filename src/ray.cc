#include "ray.hpp"
#include "vec3.hpp"

Point3 Ray::At(double t) const { return Ray::orig_ + t * Ray::dir_; }
