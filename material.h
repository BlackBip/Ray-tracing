#ifndef MATERIAL_H
#define MATERIAL_H

#include <ostream>

class Material {
  public:
    float r;
    float v;
    float b;
    float shininess;
    Material(float r_, float v_,float b_,float shininess_);
    Material() = default;
};

std::ostream & operator<< (std::ostream &st, const Material &m);

#endif