#ifndef RAY3f_H
#define RAY3f_H

#include <ostream>
#include "vector3f.h"

class Ray3f {
  public:
    Vector3f origin;
    Vector3f direction;
    Ray3f(Vector3f origin_, Vector3f direction_);
};

std::ostream & operator<< (std::ostream &st, const Ray3f &r);

#endif