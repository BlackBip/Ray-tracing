#include "quad.h"

Quad::Quad(Vector3f origin_, Vector3f width_, Vector3f height_, int matter_) {
  origin = origin_;
  width = width_;
  height = height_;
  matter = matter_;
}

bool Quad::isHit(Ray3f ray) const {
  return true;
}

Ray3f Quad::reflect(Ray3f ray) const {
  return ray;
}

std::ostream & operator<< (std::ostream &st, const Quad &q) {
  st << "Quad: " << "\n- matter: "  << q.matter << "\n- origin: " << q.origin << "\n- width: " << q.width << "\n- height: " << q.height;
  return st;
}