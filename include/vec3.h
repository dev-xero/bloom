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

    double operator[](int i) const { return elements[i]; }
    double &operator[](int i) { return elements[i]; }

    vec3 operator-() const;
    vec3 &operator+=(const vec3 &vector);
    vec3 &operator*=(const vec3 &vector);
    vec3 &operator*=(double k);
    vec3 &operator/=(double k);

    double length() const;
    double length_squared() const;
};

using point3 = vec3;

std::ostream &operator<<(std::ostream &out, const vec3 &vector);

vec3 operator+(const vec3 &u, const vec3 &v);
vec3 operator-(const vec3 &u, const vec3 &v);
vec3 operator*(const vec3 &u, const vec3 &v);
vec3 operator*(double k, const vec3 &v);
vec3 operator/(double k, const vec3 &v);

double dot(const vec3 &u, const vec3 &v);
vec3 cross(const vec3 &u, const vec3 &v);
vec3 unit(const vec3 &v);

#endif
