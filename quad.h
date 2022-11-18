#ifndef QUAD_H
#define QUAD_H

#include "vector3f.h"
#include "ray3f.h"
#include "shape.h"
#include "material.h"

class Quad : public Shape {
  public:
    Quad(Vector3f origin_, Vector3f width_, Vector3f height_, Vector3f length_, Material matter_);
    Vector3f origin;
    Vector3f width;
    Vector3f height;
    Vector3f length;
    bool isHit(Ray3f ray) const; 
    Ray3f reflect(Ray3f ray) const;
};

std::ostream & operator<< (std::ostream &st, const Quad &q);

#endif