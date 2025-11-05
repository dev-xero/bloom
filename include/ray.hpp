#ifndef RAY_HPP
#define RAY_HPP

#include "vec3.hpp"

class Ray {
  public:
    Ray() {}
    Ray(const Point3 &origin, const Vec3 &direction) : orig_(origin), dir_(direction) {}

    const Point3 &Origin() const { return orig_; }
    const Vec3 &Direction() const { return dir_; }
    Point3 At(double t) const;

  private:
    Point3 orig_;
    Vec3 dir_;
};

#endif
