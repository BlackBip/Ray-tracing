#ifndef MATERIAL_H
#define MATERIAL_H

#include <ostream>
#include "color.h"

class Material {
  public:
    Color c;
    float shininess;
    Material(Color c_, float shininess_);
    Material() = default;
};

std::ostream & operator<< (std::ostream &st, const Material &m);

#endif