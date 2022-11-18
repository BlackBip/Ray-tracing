#include "material.h"

Material::Material(float r_, float g_,float b_,float shininess_) {
  r = r_;
  g = g_;
  b = b_;
  shininess = shininess_;
}


std::ostream & operator<< (std::ostream &st, const Material &m) {
  st << "Red: " << m.r << "\nGreen: " << m.g << "\nBlue: " << m.b << "\nShininess: " << m.shininess;
  return st;
}