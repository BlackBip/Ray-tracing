#ifndef CAMERA_H
#define CAMERA_H

#include <ostream>
#include "vector3f.h"


class Camera {
  public:
    Vector3f position;
    Vector3f direction;
    float fov;
    Camera() = default;
    Camera(Vector3f position_, Vector3f direction_, float fov);
};

std::ostream & operator<< (std::ostream &st, const Camera &c);

#endif