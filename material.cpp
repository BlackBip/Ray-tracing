#include "material.h"

Material::Material(Color c_, float shininess_) {
  if (shininess_ < 0 || shininess_ > 1) 
    throw std::runtime_error("Shininess is not between 0 and 1");
  c = c_;
  shininess = shininess_;
}


std::ostream & operator<< (std::ostream &st, const Material &m) {
  st << m.c << "\nShininess: " << m.shininess;
  return st;
}