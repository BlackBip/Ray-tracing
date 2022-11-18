#ifndef SPHERE_H
#define SPHERE_H

#include "vector3f.h"
#include "ray3f.h"
#include "shape.h"

class Sphere : public Shape {
  public:
    Sphere(Vector3f origin_, float radius_, int matter_);
    Vector3f origin;
    float radius;
    bool isHit(Ray3f ray) const; 
    Ray3f reflect(Ray3f ray) const;
};

std::ostream & operator<< (std::ostream &st, const Sphere &s);

#endif