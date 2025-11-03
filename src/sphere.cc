#include "sphere.hpp"

bool Sphere::Hit(const Ray &r, Interval ray_t, HitRecord &rec) const {
  // Using vector algebra and formula of a sphere, determine whether
  // a ray hits the sphere
  //
  // (C-P).(C-P) = r^2
  // given P = Q + td,
  // (-td + (C-Q)).(-td + (C-Q)) = r^2
  //
  // Using vector algebra:
  // t^2d.d - 2td.(C-Q) + (C-Q).(C-Q) - r^2 = 0
  //
  // This is a quadratic equation solvable through the discriminant formula.
  // If D > 0, we have 2 real solutions.
  //
  // Optimization:
  // Recall that a vector dotted with itself is equal to the squared
  // length of that vector, secondly setting b = -2h, we get:
  //
  // 2h + 2(root(h^2 - ac)) / 2a
  // h + root(h^2 - ac) / a
  // b = -2d.(C-Q), and b = -2h, hence:
  // h = b/-2 = d.(C-Q)

  Vec3 oc = Sphere::center_ - r.Origin();

  auto a = r.Direction().LengthSquared();
  auto h = Dot(r.Direction(), oc);
  auto c = oc.LengthSquared() - Sphere::radius_ * Sphere::radius_;

  auto discriminant = h * h - a * c;
  if (discriminant < 0) {
    return false;
  }

  auto sqrtd = std::sqrt(discriminant);

  // We need to find the nearest root within accepted range
  auto root = (h - sqrtd) / a;
  if (!ray_t.Surrounds(root)) {
    root = (h + sqrtd) / a;
    if (!ray_t.Surrounds(root)) {
      return false;
    }
  }

  rec.t_ = root;
  rec.p_ = r.At(rec.t_);
  Vec3 outward_normal = (rec.p_ - Sphere::center_) / Sphere::radius_;
  rec.SetFaceNormal(r, outward_normal);
  rec.mat_ = Sphere::mat_;

  return true;
}
