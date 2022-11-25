#ifndef SHAPE_H
#define SHAPE_H

#include "vector3f.h"
#include "ray3f.h"
#include "material.h"

class Shape {
  public:
    Material matter;
    virtual bool isHit(Ray3f ray) const = 0; 
    virtual Ray3f reflect(Ray3f ray) const = 0;
};

bool isEnlightened(Shape** shapes, int nb_shapes, Shape* last_shape, Vector3f light, Vector3f point);

#endif