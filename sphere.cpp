#include "sphere.h"

Sphere::Sphere(Vector3f origin_, float radius_, int matter_) {
  if (radius_<0) {
    throw "Negative radius";
  }
  origin = origin_;
  radius = radius_;
  matter = matter_;
}

bool Sphere::isHit(Ray3f ray) const {
  return true;
}

Ray3f Sphere::reflect(Ray3f ray) const {
  return ray;
}

std::ostream & operator<< (std::ostream &st, const Sphere &s) {
  st << "Sphere: " << "\n- matter: "  << s.matter << "\n- origin: " << s.origin << "\n- radius: " << s.radius;
  return st;
}