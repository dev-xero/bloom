#include "vec3.hpp"
#include "common.hpp"

#include <cmath>
#include <cstdlib>
#include <iostream>

Vec3 Vec3::operator-() const { return Vec3(-elements[0], -elements[1], -elements[2]); }

Vec3 &Vec3::operator+=(const Vec3 &vector) {
    elements[0] += vector.elements[0];
    elements[1] += vector.elements[1];
    elements[2] += vector.elements[2];
    return *this;
}

Vec3 &Vec3::operator*=(double k) {
    elements[0] *= k;
    elements[1] *= k;
    elements[2] *= k;
    return *this;
}

Vec3 &Vec3::operator/=(double k) { return *this *= 1 / k; }

double Vec3::Length() const { return std::sqrt(LengthSquared()); }

double Vec3::LengthSquared() const {
    return elements[0] * elements[0] + elements[1] * elements[1] + elements[2] * elements[2];
}

bool Vec3::NearZero() const {
    const double kTHRESHOLD = 1e-8;
    return (std::fabs(Vec3::elements[0]) < kTHRESHOLD) &&
           (std::fabs(Vec3::elements[1]) < kTHRESHOLD) &&
           (std::fabs(Vec3::elements[2]) < kTHRESHOLD);
}

Vec3 Vec3::Random() { return Vec3(RandomDouble(), RandomDouble(), RandomDouble()); }

Vec3 Vec3::Random(double min, double max) {
    return Vec3(RandomDouble(min, max), RandomDouble(min, max), RandomDouble(min, max));
}

// ==================================================================
//
// VECTOR UTILITY FUNCTIONS
//
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
Vec3 Unit(const Vec3 &v) { return v / v.Length(); }

Vec3 RandomUnitVector() {
    // We want to generate a vector that falls within
    // the unit sphere, then normalize it
    while (true) {
        auto p = Vec3::Random(-1, 1);
        auto len_squared = p.LengthSquared();
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

// Reflection of a ray v given a surface normal n is given by the equation
// below.
// Negative since we want this to project out of the surface.
Vec3 Reflect(const Vec3 &v, const Vec3 &n) { return v - 2 * Dot(v, n) * n; }
