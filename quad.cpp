#include "quad.h"

Quad::Quad(Vector3f origin_, float width_, float height_, float lenght_, Material matter_) {
  origin = origin_;
  top_corner = origin+Vector3f(width_, height_, lenght_);
  matter = matter_;
}

// https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-box-intersection
bool Quad::isHit(Ray3f ray) const {
  float tmin = (origin.x - ray.origin.x) / ray.direction.x; 
  float tmax = (top_corner.x - ray.origin.x) / ray.direction.x; 

  if (tmin > tmax) std::swap(tmin, tmax); 

  float tymin = (origin.y - ray.origin.y) / ray.direction.y; 
  float tymax = (top_corner.y - ray.origin.y) / ray.direction.y; 

  if (tymin > tymax) std::swap(tymin, tymax); 

  if ((tmin > tymax) || (tymin > tmax)) 
      return false; 

  if (tymin > tmin) 
      tmin = tymin; 

  if (tymax < tmax) 
      tmax = tymax; 

  float tzmin = (origin.z - ray.origin.z) / ray.direction.z; 
  float tzmax = (top_corner.z - ray.origin.z) / ray.direction.z; 

  if (tzmin > tzmax) std::swap(tzmin, tzmax); 

  if ((tmin > tzmax) || (tzmin > tmax)) 
      return false; 

  if (tzmin > tmin) 
      tmin = tzmin; 

  if (tzmax < tmax) 
      tmax = tzmax;

  if (tmin < 0)
    return false;

  return true;
} // CHANGER LE CODE EST VOLE

Ray3f Quad::reflect(Ray3f ray) const {
  float tmin = (origin.x - ray.origin.x) / ray.direction.x; 
  float tmax = (top_corner.x - ray.origin.x) / ray.direction.x; 

  if (tmin > tmax) std::swap(tmin, tmax); 

  float tymin = (origin.y - ray.origin.y) / ray.direction.y; 
  float tymax = (top_corner.y - ray.origin.y) / ray.direction.y; 

  if (tymin > tymax) std::swap(tymin, tymax); 

  if (tymin > tmin) 
      tmin = tymin; 

  if (tymax < tmax) 
      tmax = tymax; 

  float tzmin = (origin.z - ray.origin.z) / ray.direction.z; 
  float tzmax = (top_corner.z - ray.origin.z) / ray.direction.z; 

  if (tzmin > tzmax) std::swap(tzmin, tzmax); 

  if (tzmin > tmin) 
      tmin = tzmin; 

  Vector3f intersection = ray.origin + tmin*ray.direction;
  Vector3f N;

  if(std::abs(intersection.x - origin.x) < 1e-3)
    N = Vector3f(-1.0, 0.0, 0.0);
  else if (std::abs(intersection.x - top_corner.x) < 1e-3)
    N = Vector3f(1.0, 0.0, 0.0);
  else if (std::abs(intersection.y - origin.y) < 1e-3)
    N = Vector3f(0.0, -1.0, 0.0);
  else if (std::abs(intersection.y - top_corner.y) < 1e-3)
    N = Vector3f(0.0, 1.0, 0.0);
  else if (std::abs(intersection.z - origin.z) < 1e-3)
    N = Vector3f(0.0, 0.0, -1.0);
  else if (std::abs(intersection.z - top_corner.z) < 1e-3)
    N = Vector3f(0.0, 0.0, 1.0);
  
  return Ray3f(intersection, -2*dot_product(ray.direction, N)*N+ray.direction);
}

std::ostream & operator<< (std::ostream &st, const Quad &q) {
  st << "Quad: " << "\n- matter: "  << q.matter << "\n- origin: " << q.origin << "\n- width: " << q.top_corner.x << "\n- height: " << q.top_corner.y << "\n- length: " << q.top_corner.z;
  return st;
}