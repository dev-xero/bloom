#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

class vec3 {
  public:
    double elements[3];

    vec3() : elements{0, 0, 0} {}
    vec3(double e0, double e1, double e2) : elements{e0, e1, e2} {}

    double x() const { return elements[0]; }
    double y() const { return elements[1]; }
    double z() const { return elements[2]; }

    // new negative vector
    vec3 operator-() const { return vec3(-elements[0], -elements[1], -elements[2]); }
    // access (read only)
    double operator[](int i) const { return elements[i]; }
    // access (mutable)
    double &operator[](int i) { return elements[i]; }

    // add vectors uniformly
    vec3 &operator+=(const vec3 &vector) {
        elements[0] += vector.elements[0];
        elements[1] += vector.elements[1];
        elements[2] += vector.elements[2];
        return *this;
    }

    // scale uniformly
    vec3 &operator*=(double k) {
        elements[0] *= k;
        elements[1] *= k;
        elements[2] *= k;
        return *this;
    }

    // scale by division, uniformly
    vec3 &operator/=(double k) { return *this *= 1 / k; }

    double length() const { return std::sqrt(length_squared()); }

    double length_squared() const {
        return elements[0] * elements[0] + elements[1] * elements[1] + elements[2] * elements[2];
    }
};

using point3 = vec3;

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

// The unit vector
inline vec3 unit_vector(const vec3 &v) { return v / v.length(); }

#endif
