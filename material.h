#ifndef MATERIAL_H
#define MATERIAL_H

#include <ostream>

class Material {
  public:
    float r;
    float g;
    float b;
    float shininess;
    Material(float r_, float g_,float b_,float shininess_);
    Material() = default;
};

std::ostream & operator<< (std::ostream &st, const Material &m);

#endif