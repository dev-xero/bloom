#include "vec3.hpp"
#include "common.hpp"

#include <cmath>
#include <cstdlib>
#include <iostream>

// Negate vector
Vec3 Vec3::operator-() const { return Vec3(-elements[0], -elements[1], -elements[2]); }

// Add vectors uniformly
Vec3 &Vec3::operator+=(const Vec3 &vector) {
    elements[0] += vector.elements[0];
    elements[1] += vector.elements[1];
    elements[2] += vector.elements[2];
    return *this;
}

// Scale uniformly
Vec3 &Vec3::operator*=(double k) {
    elements[0] *= k;
    elements[1] *= k;
    elements[2] *= k;
    return *this;
}

// Scale by 1/k, uniformly
Vec3 &Vec3::operator/=(double k) { return *this *= 1 / k; }

// Length is given by square root of components squared
double Vec3::length() const { return std::sqrt(length_squared()); }

// Computes the sum of squares of the components
double Vec3::length_squared() const {
    return elements[0] * elements[0] + elements[1] * elements[1] + elements[2] * elements[2];
}

Vec3 Vec3::random() { return Vec3(random_double(), random_double(), random_double()); }

Vec3 Vec3::random(double min, double max) {
    return Vec3(random_double(min, max), random_double(min, max), random_double(min, max));
}

// ==================================================================
// VECTOR UTILITY FUNCTIONS
// ==================================================================

// Need a way to print vector information
std::ostream &operator<<(std::ostream &out, const Vec3 &vector) {
    return out << vector.elements[0] << ' ' << vector.elements[1] << ' ' << vector.elements[2];
}

Vec3 operator+(const Vec3 &u, const Vec3 &v) {
    return Vec3(u.elements[0] + v.elements[0], u.elements[1] + v.elements[1],
                u.elements[2] + v.elements[2]);
}

Vec3 operator-(const Vec3 &u, const Vec3 &v) {
    return Vec3(u.elements[0] - v.elements[0], u.elements[1] - v.elements[1],
                u.elements[2] - v.elements[2]);
}

Vec3 operator*(const Vec3 &u, const Vec3 &v) {
    return Vec3(u.elements[0] * v.elements[0], u.elements[1] * v.elements[1],
                u.elements[2] * v.elements[2]);
}

Vec3 operator*(double k, const Vec3 &v) {
    return Vec3(k * v.elements[0], k * v.elements[1], k * v.elements[2]);
}

// Needed for situations where we have k * v
Vec3 operator*(const Vec3 &v, double k) { return k * v; }

Vec3 operator/(const Vec3 &v, double k) { return (1 / k) * v; }

// Vector Dot Product: u1*v1 + u2*v2 + u3*v3
double Dot(const Vec3 &u, const Vec3 &v) {
    return u.elements[0] * v.elements[0] + u.elements[1] * v.elements[1] +
           u.elements[2] * v.elements[2];
}

// Vector Cross Product: U x V
// U = [a, b, c]
// V = [d, e, f]
// U x V = [(bf - ce), (cd - af), (ae - bd)]
Vec3 Cross(const Vec3 &v, const Vec3 &u) {
    return Vec3(u.elements[1] * v.elements[2] - u.elements[2] * v.elements[1],
                u.elements[2] * v.elements[0] - u.elements[0] * v.elements[2],
                u.elements[0] * v.elements[1] - u.elements[1] * v.elements[0]);
}

// Mathematically accurate unit vector
Vec3 Unit(const Vec3 &v) { return v / v.length(); }

Vec3 RandomUnitVector() {
    // We want to generate a vector that falls within
    // the unit sphere, then normalize it
    while (true) {
        auto p = Vec3::random(-1, 1);
        auto len_squared = p.length_squared();
        // need to account for really small values
        // of len_sq to avoid underflowing to zero
        if (1e-160 < len_squared && len_squared <= 1)
            return p / sqrt(len_squared);
    }
}

Vec3 RandomOnHemisphere(const Vec3 &normal) {
    Vec3 on_unit_sphere = RandomUnitVector();
    // the dot product tells us how much two vectors
    // point in the same direction
    if (Dot(on_unit_sphere, normal) > 0.0) {
        return on_unit_sphere;
    } else {
        // reversing direction since this way
        // we're bound to point in the direction
        // of the surface normal
        return -on_unit_sphere;
    }
}
