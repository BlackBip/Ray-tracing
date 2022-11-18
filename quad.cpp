#include "quad.h"

Quad::Quad(Vector3f origin_, Vector3f width_, Vector3f height_, Vector3f lenght_, Material matter_) {
  origin = origin_;
  width = width_;
  length = lenght_;
  height = height_;
  matter = matter_;
}

// https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-box-intersection
bool Quad::isHit(Ray3f ray) const {
  Vector3f vmin = origin;
  Vector3f vmax = origin+height+length+width;

  float tmin = (vmin.x - ray.origin.x) / ray.direction.x; 
  float tmax = (vmax.x - ray.origin.x) / ray.direction.x; 

  if (tmin > tmax) std::swap(tmin, tmax); 

  float tymin = (vmin.y - ray.origin.y) / ray.direction.y; 
  float tymax = (vmax.y - ray.origin.y) / ray.direction.y; 

  if (tymin > tymax) std::swap(tymin, tymax); 

  if ((tmin > tymax) || (tymin > tmax)) 
      return false; 

  if (tymin > tmin) 
      tmin = tymin; 

  if (tymax < tmax) 
      tmax = tymax; 

  float tzmin = (vmin.z - ray.origin.z) / ray.direction.z; 
  float tzmax = (vmax.z - ray.origin.z) / ray.direction.z; 

  if (tzmin > tzmax) std::swap(tzmin, tzmax); 

  if ((tmin > tzmax) || (tzmin > tmax)) 
      return false; 

  if (tzmin > tmin) 
      tmin = tzmin; 

  if (tzmax < tmax) 
      tmax = tzmax;

  return true;
} // CHANGER LE CODE EST VOLE

Ray3f Quad::reflect(Ray3f ray) const {
  return ray;
}

std::ostream & operator<< (std::ostream &st, const Quad &q) {
  st << "Quad: " << "\n- matter: "  << q.matter << "\n- origin: " << q.origin << "\n- width: " << q.width << "\n- height: " << q.height;
  return st;
}