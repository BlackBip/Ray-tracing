#include "material.h"

Material::Material(float r_, float g_,float b_,float shininess_) {
  if ( r_ < 0 || r_ > 1 || g_ < 0 || g_ > 1 || b_ < 0 || b_ > 1 || shininess_ < 0 || shininess_ > 1 ) 
    throw std::runtime_error(" r, g, b or shininess are not in the great domaine");
  r = r_;
  g = g_;
  b = b_;
  shininess = shininess_;
}


std::ostream & operator<< (std::ostream &st, const Material &m) {
  st << "Red: " << m.r << "\nGreen: " << m.g << "\nBlue: " << m.b << "\nShininess: " << m.shininess;
  return st;
}