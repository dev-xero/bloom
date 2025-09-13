#include "vec3.h"
#include "common.h"

#include <cmath>
#include <cstdlib>
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

vec3 vec3::random() { return vec3(random_double(), random_double(), random_double()); }

vec3 vec3::random(double min, double max) {
    return vec3(random_double(min, max), random_double(min, max), random_double(min, max));
}

// ==================================================================
// VECTOR UTILITY FUNCTIONS
// ==================================================================

// Need a way to print vector information
std::ostream &operator<<(std::ostream &out, const vec3 &vector) {
    return out << vector.elements[0] << ' ' << vector.elements[1] << ' ' << vector.elements[2];
}

// Adding two vectors
vec3 operator+(const vec3 &u, const vec3 &v) {
    return vec3(u.elements[0] + v.elements[0], u.elements[1] + v.elements[1],
                u.elements[2] + v.elements[2]);
}

// Subtracting two vectors
vec3 operator-(const vec3 &u, const vec3 &v) {
    return vec3(u.elements[0] - v.elements[0], u.elements[1] - v.elements[1],
                u.elements[2] - v.elements[2]);
}

// Multiplying two vectors
vec3 operator*(const vec3 &u, const vec3 &v) {
    return vec3(u.elements[0] * v.elements[0], u.elements[1] * v.elements[1],
                u.elements[2] * v.elements[2]);
}

// Scaling a vector by k
vec3 operator*(double k, const vec3 &v) {
    return vec3(k * v.elements[0], k * v.elements[1], k * v.elements[2]);
}

// Needed for situations where we have k * v
vec3 operator*(const vec3 &v, double k) { return k * v; }

// Scaling a vector by 1/k
vec3 operator/(const vec3 &v, double k) { return (1 / k) * v; }

// Vector Dot Product: u1*v1 + u2*v2 + u3*v3
double dot(const vec3 &u, const vec3 &v) {
    return u.elements[0] * v.elements[0] + u.elements[1] * v.elements[1] +
           u.elements[2] * v.elements[2];
}

// Vector Cross Product: U x V
// U = [a, b, c]
// V = [d, e, f]
// U x V = [(bf - ce), (cd - af), (ae - bd)]
vec3 cross(const vec3 &v, const vec3 &u) {
    return vec3(u.elements[1] * v.elements[2] - u.elements[2] * v.elements[1],
                u.elements[2] * v.elements[0] - u.elements[0] * v.elements[2],
                u.elements[0] * v.elements[1] - u.elements[1] * v.elements[0]);
}

// Mathematically accurate unit vector
vec3 unit(const vec3 &v) { return v / v.length(); }

vec3 random_unit_vector() {
    // We want to generate a vector that falls within
    // the unit sphere, then normalize it
    while (true) {
        auto p = vec3::random(-1, 1);
        auto len_squared = p.length_squared();
        // need to account for really small values
        // of len_sq to avoid underflowing to zero
        if (1e-160 < len_squared && len_squared <= 1)
            return p / sqrt(len_squared);
    }
}

vec3 random_on_hemisphere(const vec3 &normal) {
    vec3 on_unit_sphere = random_unit_vector();
    // the dot product tells us how much two vectors
    // point in the same direction
    if (dot(on_unit_sphere, normal) > 0.0) {
        return on_unit_sphere;
    } else {
        // reversing direction since this way
        // we're bound to point in the direction
        // of the surface normal
        return -on_unit_sphere;
    }
}
