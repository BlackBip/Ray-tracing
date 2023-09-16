#include "camera.h"

Camera::Camera(Vector3f position_, Vector3f direction_, float fov_) {
  if ( fov_ < 0 || fov_ > 3.14 ) 
    throw std::runtime_error("fov is not in between 0 and pi");
  position = position_;
  direction = direction_;
  fov = fov_;
}

std::ostream & operator<< (std::ostream &st, const Camera &c) {
  st << "position: " << c.position << "\ndirection: " << c.direction<< "\nfov: " << c.fov;
  return st;
}