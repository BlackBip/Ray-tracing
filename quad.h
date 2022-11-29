#ifndef QUAD_H
#define QUAD_H

#include "vector3f.h"
#include "ray3f.h"
#include "shape.h"
#include "material.h"

class Quad : public Shape {
  private:
    mutable float tmin;
    mutable bool isHitCalled;
  public:
    Quad(Vector3f origin_, float width_, float height_, float length_, Material matter_);
    Vector3f origin;
    Vector3f top_corner;
    bool isHit(Ray3f ray) const; 
    Ray3f reflect(Ray3f ray) const;
};

std::ostream & operator<< (std::ostream &st, const Quad &q);

#endif