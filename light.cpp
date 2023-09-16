#include "light.h"

Light::Light(Vector3f position_, float intensity_) {
  if ( intensity_ < 0 || intensity_ > 1 ) 
    throw std::runtime_error("intensity is not between 0 and 1");
  position = position_;
  intensity = intensity_;
}

std::ostream & operator<< (std::ostream &st, const Light &l) {
  st << "position: " << l.position << "\nitensity: " << l.intensity;
  return st;
}