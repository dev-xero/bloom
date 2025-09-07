#ifndef COMMON_H
#define COMMON_H

#include <cmath>
#include <limits>
#include <memory>

// Std Usings
using std::make_shared;
using std::shared_ptr;

// Constants
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility functions
inline double degrees_to_radians(double degrees) { return degrees * pi / 180.0; }

#endif
