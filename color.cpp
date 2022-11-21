#include "color.h"

Color::Color(float r_, float g_,float b_) {
  if ( r_ < 0 || r_ > 1 || g_ < 0 || g_ > 1 || b_ < 0 || b_ > 1) 
    throw std::runtime_error(" r, g, b or shininess are not in the great domaine");
  r = r_;
  g = g_;
  b = b_;
}


std::ostream & operator<< (std::ostream &st, const Color &c) {
  st << "Red: " << c.r << "\nGreen: " << c.g << "\nBlue: " << c.b;
  return st;
}


Color & Color::operator+=(Color c) {
  return *this = Color(r+c.r, g+c.g, b+c.b);
}

Color & Color::operator*=(Color c) {
  return *this = Color(r*c.r, g*c.g, b*c.b);
}

Color operator+ (const Color &c1, const Color &c2) {
  return Color(c1)+=c2;
}


Color operator* (const Color &c1, const Color &c2) {
  return Color(c1)*=c2;
}
