#include "vec3.h"

#include <cmath>
#include <iostream>

// Negate vector
vec3 vec3::operator-() const { return vec3(-elements[0], -elements[1], -elements[2]); }

// Add vectors uniformly
vec3 &vec3::operator+=(const vec3 &vector) {
    elements[0] += vector.elements[0];
    elements[1] += vector.elements[1];
    elements[2] += vector.elements[2];
    return *this;
}

// Scale uniformly
vec3 &vec3::operator*=(double k) {
    elements[0] *= k;
    elements[1] *= k;
    elements[2] *= k;
    return *this;
}

// Scale by 1/k, uniformly
vec3 &vec3::operator/=(double k) { return *this *= 1 / k; }

// Length is given by square root of components squared
double vec3::length() const { return std::sqrt(length_squared()); }

// Computes the sum of squares of the components
double vec3::length_squared() const {
    return elements[0] * elements[0] + elements[1] * elements[1] + elements[2] * elements[2];
}

// ==================================================================
// VECTOR UTILITY FUNCTIONS
// ==================================================================

// Need a way to print vector information
inline std::ostream &operator<<(std::ostream &out, const vec3 &vector) {
    return out << vector.elements[0] << ' ' << vector.elements[1] << ' ' << vector.elements[2];
}

// Adding two vectors
inline vec3 operator+(const vec3 &u, const vec3 &v) {
    return vec3(u.elements[0] + v.elements[0], u.elements[1] + v.elements[1],
                u.elements[2] + v.elements[2]);
}

// Subtracting two vectors
inline vec3 operator-(const vec3 &u, const vec3 &v) {
    return vec3(u.elements[0] - v.elements[0], u.elements[1] - v.elements[1],
                u.elements[2] - v.elements[2]);
}

// Multiplying two vectors
inline vec3 operator*(const vec3 &u, const vec3 &v) {
    return vec3(u.elements[0] * v.elements[0], u.elements[1] * v.elements[1],
                u.elements[2] * v.elements[2]);
}

// Scaling a vector by k
inline vec3 operator*(double k, const vec3 &v) {
    return vec3(k * v.elements[0], k * v.elements[1], k * v.elements[2]);
}

// Needed for situations where we have k * v
inline vec3 operator*(const vec3 &v, double k) { return k * v; }

// Scaling a vector by 1/k
inline vec3 operator/(const vec3 &v, double k) { return (1 / k) * v; }

// Vector Dot Product: u1*v1 + u2*v2 + u3*v3
inline double dot(const vec3 &u, const vec3 &v) {
    return u.elements[0] * v.elements[0] + u.elements[1] * v.elements[1] +
           u.elements[2] * v.elements[2];
}

// Vector Cross Product: U x V
// U = [a, b, c]
// V = [d, e, f]
// U x V = [(bf - ce), (cd - af), (ae - bd)]
inline vec3 cross(const vec3 &v, const vec3 &u) {
    return vec3(u.elements[1] * v.elements[2] - u.elements[2] * v.elements[1],
                u.elements[2] * v.elements[0] - u.elements[0] * v.elements[2],
                u.elements[0] * v.elements[1] - u.elements[1] * v.elements[0]);
}

// Mathematically accurate unit vector
inline vec3 unit_vector(const vec3 &v) { return v / v.length(); }
