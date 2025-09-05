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

#endif
