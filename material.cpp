#include "material.h"

Material::Material(float r_, float v_, float b_, float shininess_) {
  r = r_;
  v = v_;
  b = b_;
  shininess = shininess_;
}


std::ostream & operator<< (std::ostream &st, const Material &m) {
  st << "Rouge: " << m.r << "\nVert: " << m.v << "\nBleu: " << m.b << "\nShininess: " << m.shininess;
  return st;
}