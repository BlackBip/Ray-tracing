#include "ray3f.h"

Ray3f::Ray3f(Vector3f origin_, Vector3f direction_) {
  origin = origin_;
  direction = direction_;
}

std::ostream & operator<< (std::ostream &st, const Ray3f &r) {
  st << "origin: " << r.origin << "\ndirection: " << r.direction;
  return st;
}