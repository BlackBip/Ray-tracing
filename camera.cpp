#include "camera.h"

Camera::Camera(Vector3f position_, Vector3f direction_) {
  position = position_;
  direction = direction_;
}

std::ostream & operator<< (std::ostream &st, const Camera &c) {
  st << "position: " << c.position << "\ndirection: " << c.direction;
  return st;
}