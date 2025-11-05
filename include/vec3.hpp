#ifndef VEC3_HPP
#define VEC3_HPP

#include <iostream>

class Vec3 {
public:
  double elements[3];

  Vec3() : elements{0, 0, 0} {}
  Vec3(double e0, double e1, double e2) : elements{e0, e1, e2} {}

  double x() const { return elements[0]; }
  double y() const { return elements[1]; }
  double z() const { return elements[2]; }

  double operator[](int i) const { return elements[i]; }
  double &operator[](int i) { return elements[i]; }

  Vec3 operator-() const;
  Vec3 &operator+=(const Vec3 &vector);
  Vec3 &operator*=(const Vec3 &vector);
  Vec3 &operator*=(double k);
  Vec3 &operator/=(double k);

  double Length() const;
  double LengthSquared() const;
  bool NearZero() const;

  static Vec3 Random();
  static Vec3 Random(double min, double max);
};

using Point3 = Vec3;

std::ostream &operator<<(std::ostream &out, const Vec3 &vector);

Vec3 operator+(const Vec3 &u, const Vec3 &v);
Vec3 operator-(const Vec3 &u, const Vec3 &v);
Vec3 operator*(const Vec3 &u, const Vec3 &v);
Vec3 operator*(double k, const Vec3 &v);
Vec3 operator*(const Vec3 &v, double t);
Vec3 operator/(const Vec3 &v, double t);

double Dot(const Vec3 &u, const Vec3 &v);
Vec3 Cross(const Vec3 &u, const Vec3 &v);
Vec3 Unit(const Vec3 &v);

Vec3 RandomUnitVector();
Vec3 RandomOnHemisphere(const Vec3 &normal);
Vec3 Reflect(const Vec3 &v, const Vec3 &n);

#endif
