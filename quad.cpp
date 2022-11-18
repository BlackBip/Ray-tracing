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
  Vector3f vmin = origin;
  Vector3f vmax = origin+height+length+width;

  Vector3f u_hat = ray.direction/norm(ray.direction);

  float tmin = (vmin.x - ray.origin.x) / u_hat.x; 
  float tmax = (vmax.x - ray.origin.x) / u_hat.x; 

  if (tmin > tmax) std::swap(tmin, tmax); 

  float tymin = (vmin.y - ray.origin.y) / u_hat.y; 
  float tymax = (vmax.y - ray.origin.y) / u_hat.y; 

  if (tymin > tymax) std::swap(tymin, tymax); 

  if (tymin > tmin) 
      tmin = tymin; 

  if (tymax < tmax) 
      tmax = tymax; 

  float tzmin = (vmin.z - ray.origin.z) / u_hat.z; 
  float tzmax = (vmax.z - ray.origin.z) / u_hat.z; 

  if (tzmin > tzmax) std::swap(tzmin, tzmax);

  if (tzmin > tmin) 
      tmin = tzmin; 

  if (tzmax < tmax) 
      tmax = tzmax;

  Vector3f intersection = ray.origin + tmin*u_hat;
  Vector3f N;

  float cx = abs(intersection.x - vmin.x);
  float fx = abs(intersection.x - vmax.x);
  float cy = abs(intersection.y - vmin.y);
  float fy = abs(intersection.y - vmax.y);
  float cz = abs(intersection.z - vmin.z);
  float fz = abs(intersection.z - vmax.z);

  if(cx < 1e-3)
    N = Vector3f(-1.0, 0.0, 0.0);
  else if (fx < 1e-3)
    N = Vector3f(1.0, 0.0, 0.0);
  else if (cy < 1e-3)
    N = Vector3f(0.0, -1.0, 0.0);
  else if (fy < 1e-3)
    N = Vector3f(0.0, 1.0, 0.0);
  else if (cz < 1e-3)
    N = Vector3f(0.0, 0.0, -1.0);
  else if (fz < 1e-3)
    N = Vector3f(0.0, 0.0, 1.0);

  return Ray3f(intersection, -2*dot_product(u_hat, N)*N+u_hat);
}

std::ostream & operator<< (std::ostream &st, const Quad &q) {
  st << "Quad: " << "\n- matter: "  << q.matter << "\n- origin: " << q.origin << "\n- width: " << q.width << "\n- height: " << q.height;
  return st;
}