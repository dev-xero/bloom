#ifndef COMMON_HPP
#define COMMON_HPP

#include <cstdlib>
#include <limits>
#include <memory>

// Std Usings
using std::make_shared;
using std::shared_ptr;

// Constants
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility functions
inline double DegreesToRadians(double degrees) { return degrees * pi / 180.0; }

inline double RandomDouble() {
    // returns a random real in [0, 1)
    return std::rand() / (RAND_MAX + 1.0);
}

inline double RandomDouble(double min, double max) {
    // returns a random real in [min, max]
    return min + (max - min) * RandomDouble();
}

#endif
