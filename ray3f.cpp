#include "ray3f.h"

Ray3f::Ray3f(Vector3f origin_, Vector3f direction_) {
  origin = origin_;
  float direction_norm = norm(direction_);
  if (direction_norm<1e-3) {
    throw "Direction can't be 0";
  }
  direction = direction_/direction_norm;
}

std::ostream & operator<< (std::ostream &st, const Ray3f &r) {
  st << "origin: " << r.origin << "\ndirection: " << r.direction;
  return st;
}