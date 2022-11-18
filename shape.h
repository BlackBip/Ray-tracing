#ifndef SHAPE_H
#define SHAPE_H

#include "ray3f.h"
#include "material.h"

class Shape {
  public:
    Material matter;
    virtual bool isHit(Ray3f ray) const = 0; 
    virtual Ray3f reflect(Ray3f ray) const = 0;
};

#endif