#ifndef COLOR_H
#define COLOR_H

#include <ostream>

class Color {
  public:
    float r;
    float g;
    float b;
    Color(float r_ = 0., float g_ = 0.,float b_ = 0.);
    Color & operator+=(Color c);
    Color & operator*=(Color c);
};


Color operator+ (const Color &c1, const Color &c2);
Color operator* (const Color &c1, const Color &c2);


#endif