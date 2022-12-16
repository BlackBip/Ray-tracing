#include "quad.h"

Quad::Quad(Vector3f origin_, float width_, float height_, float length_, Material matter_) {
  if ( width_ < 0 || height_ < 0 || length_ < 0 ) 
    throw std::runtime_error("width, height or length is negative");
  origin = origin_;
  top_corner = origin + Vector3f(width_, height_, length_);
  matter = matter_;
}

// The idea of using the planes of the rectangular cuboid comes from this article :
// https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-box-intersection
// Note : the provided C++ implementation was not used, it is probably faster but also less understandable
bool Quad::isHit(Ray3f ray) const {

  Vector3f origin_ray = origin - ray.origin;
  Vector3f top_ray = top_corner - ray.origin;

  // Ray path : ray.origin + t*ray.direction with t>=0
  // Compute the different values of t that would hit each combinaisons of the parallels planes defined by the rectangular cuboid

  float t_first_hit_x = origin_ray.x / ray.direction.x;
  float t_second_hit_x = top_ray.x / ray.direction.x;

  if (t_first_hit_x > t_second_hit_x) std::swap(t_first_hit_x, t_second_hit_x);

  float t_first_hit_y = origin_ray.y / ray.direction.y;
  float t_second_hit_y = top_ray.y / ray.direction.y;

  if (t_first_hit_y > t_second_hit_y) std::swap(t_first_hit_y, t_second_hit_y);

  float t_first_hit_z = origin_ray.z / ray.direction.z; 
  float t_second_hit_z = top_ray.z / ray.direction.z; 

  if (t_first_hit_z > t_second_hit_z) std::swap(t_first_hit_z, t_second_hit_z); 

  // Check if max(t_first_hit_x,t_first_hit_y,t_first_hit_z) < min(t_second_hit_x,t_second_hit_y,t_second_hit_z)
  // to ensure that the ray enters each plane of the rectangular cuboid before leaving any

  float t_first_hit = std::max(t_first_hit_x, std::max(t_first_hit_y, t_first_hit_z));
  float t_second_hit = std::min(t_second_hit_x, std::min(t_second_hit_y, t_second_hit_z));

  if (t_first_hit > t_second_hit)
    return false;

  // Ensure that the collision happens with a positive t, as the light travels in a set direction
  // t_second_hit was constructed be be greater than t_first_hit
  return t_second_hit > 0;
}

// The reflection formula comes from this article :
// http://www.3dkingdoms.com/weekly/weekly.php?a=2
Ray3f Quad::reflect(Ray3f ray) const {

  // Compute t_first_hit and t_second_hit again

  Vector3f origin_ray = origin - ray.origin;
  Vector3f top_ray = top_corner - ray.origin;

  float t_first_hit_x = origin_ray.x / ray.direction.x;
  float t_second_hit_x = top_ray.x / ray.direction.x;

  if (t_first_hit_x > t_second_hit_x) std::swap(t_first_hit_x, t_second_hit_x);

  float t_first_hit_y = origin_ray.y / ray.direction.y;
  float t_second_hit_y = top_ray.y / ray.direction.y;

  if (t_first_hit_y > t_second_hit_y) std::swap(t_first_hit_y, t_second_hit_y);

  float t_first_hit_z = origin_ray.z / ray.direction.z; 
  float t_second_hit_z = top_ray.z / ray.direction.z; 

  if (t_first_hit_z > t_second_hit_z) std::swap(t_first_hit_z, t_second_hit_z); 

  float t_first_hit = std::max(t_first_hit_x, std::max(t_first_hit_y, t_first_hit_z));
  float t_second_hit = std::min(t_second_hit_x, std::min(t_second_hit_y, t_second_hit_z));

  // Find the smallest positive t that the intersect rectangular cuboid. It exists has this function is meant to
  // be called after isHit.
  float t_first_positive_hit = (t_first_hit<0) ? t_second_hit : t_first_hit;

  // Compute the intersection
  Vector3f intersection = ray.origin + t_first_positive_hit*ray.direction; 
  Vector3f N;

  // Find which side of the regular cuboid was hit by the ray to compute the normal vector
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
  
  // Compute the reflection
  return Ray3f(intersection, -2*dot_product(ray.direction, N)*N+ray.direction);
}

std::ostream & operator<< (std::ostream &st, const Quad &q) {
  st << "Quad: " << "\n- matter: "  << q.matter << "\n- origin: " << q.origin << "\n- width: " << q.top_corner.x << "\n- height: " << q.top_corner.y << "\n- length: " << q.top_corner.z;
  return st;
}