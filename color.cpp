#include "color.h"

Color::Color(float r_, float g_,float b_) {
  if ( r_ < 0 || r_ > 1 || g_ < 0 || g_ > 1 || b_ < 0 || b_ > 1) 
    throw std::runtime_error("r, g or b is not between 0 and 1");
  r = r_;
  g = g_;
  b = b_;
}

int floatToInt(float f) {
  f *= 255.;
  return static_cast<int>(f + 0.5 - (f<0));
}

std::ostream & operator<< (std::ostream &st, const Color &c) {
  st << "Red: " << c.r << "\nGreen: " << c.g << "\nBlue: " << c.b;
  return st;
}

Color & Color::operator+=(Color c) {
  return *this = Color(r+c.r, g+c.g, b+c.b);
}

Color & Color::operator*=(float f) {
  return *this = Color(r*f, g*f, b*f);
}

Color operator+ (const Color &c1, const Color &c2) {
  return Color(c1)+=c2;
}

Color operator* (float f, const Color &c) {
  return Color(c)*=f;
}