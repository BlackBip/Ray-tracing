#include <cmath>
#include "sphere.h"

Sphere::Sphere(Vector3f origin_, float radius_, Material matter_) {
  if (radius_<0) {
    throw std::runtime_error("Negative radius");
  }
  origin = origin_;
  radius = radius_;
  matter = matter_;
}

// https://en.wikipedia.org/wiki/Line%E2%80%93sphere_intersection
bool Sphere::isHit(Ray3f ray) const {
  float delta = pow(dot_product(ray.direction,ray.origin-origin),2) - (pow(norm(ray.origin-origin),2)-pow(radius,2));
  return (delta>0); // voir pour mettre un 1e-3 ou quoi
}

// https://en.wikipedia.org/wiki/Line%E2%80%93sphere_intersection
// http://www.3dkingdoms.com/weekly/weekly.php?a=2
Ray3f Sphere::reflect(Ray3f ray) const {
  float delta = pow(dot_product(ray.direction,ray.origin-origin),2) - (pow(norm(ray.origin-origin),2)-pow(radius,2));

  float d1 = -dot_product(ray.direction,ray.origin-origin)-sqrt(delta);
  float d2 = -dot_product(ray.direction,ray.origin-origin)+sqrt(delta);
  Vector3f intersection;
  if (d1>0)
    intersection = ray.origin + d1*ray.direction;
  else
    intersection = ray.origin + d2*ray.direction;

  Vector3f N = origin - intersection;
  return Ray3f(intersection, -2*dot_product(ray.direction, N)*N+ray.direction);
}

std::ostream & operator<< (std::ostream &st, const Sphere &s) {
  st << "Sphere: " << "\n- matter: "  << s.matter << "\n- origin: " << s.origin << "\n- radius: " << s.radius;
  return st;
}