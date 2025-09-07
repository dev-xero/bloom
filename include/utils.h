#ifndef UTILS_H
#define UTILS_H

#include <cmath>
#include <iostream>
#include <limits>
#include <memory>

// Std Usings
using std::make_shared;
using std::shared_ptr;

// Constants
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility functions
double degrees_to_radians(double degrees) { return degrees * pi / 180.0; }

// Common headers
#include "color.h"
#include "ray.h"
#include "vec3.h"

#endif
