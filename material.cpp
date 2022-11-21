#include "material.h"

Material::Material(Color c_, float shininess_) {
  if (shininess_ < 0 || shininess_ > 1) 
    throw std::runtime_error("Shininess is not in the good domain");
  c = c_;
  shininess = shininess_;
}


std::ostream & operator<< (std::ostream &st, const Material &m) {
  st << m.c << "\nShininess: " << m.shininess;
  return st;
}