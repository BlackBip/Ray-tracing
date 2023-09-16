#include <cmath>
#include "sphere.h"

Sphere::Sphere(Vector3f origin_, float radius_, Material matter_) {
  if (radius_<0) {
    throw std::runtime_error("Radius is negative");
  }
  origin = origin_;
  radius = radius_;
  matter = matter_;
}

// The line–sphere intersection criteria comes from this page :
// https://en.wikipedia.org/wiki/Line%E2%80%93sphere_intersection
bool Sphere::isHit(Ray3f ray) const {
  float delta = pow(dot_product(ray.direction,ray.origin-origin),2) - (pow(norm(ray.origin-origin),2)-pow(radius,2));

  // We can't just use delta>0 has light has a direction and the intersecion might be on the wrong 'side'
  return -dot_product(ray.direction,ray.origin-origin)+sqrt(delta)>0;
}

// The reflection formula comes from this article :
// http://www.3dkingdoms.com/weekly/weekly.php?a=2
Ray3f Sphere::reflect(Ray3f ray) const {

  // Compute delta again
  float delta = pow(dot_product(ray.direction,ray.origin-origin),2) - (pow(norm(ray.origin-origin),2)-pow(radius,2));

  float d1 = -dot_product(ray.direction,ray.origin-origin)-sqrt(delta);
  float d2 = -dot_product(ray.direction,ray.origin-origin)+sqrt(delta);

  // Find the smallest positive t that the intersect sphere. It exists has this function is meant to
  // be called after isHit.
  float t_first_positive_hit = (d1<0) ? d2 : d1;

  // Compute the intersection
  Vector3f intersection = ray.origin + t_first_positive_hit*ray.direction;

  // Compute the normal vector
  Vector3f N = origin - intersection;

  // Compute the reflection
  return Ray3f(intersection, -2*dot_product(ray.direction, N)*N+ray.direction);
}

std::ostream & operator<< (std::ostream &st, const Sphere &s) {
  st << "Sphere: " << "\n- matter: "  << s.matter << "\n- origin: " << s.origin << "\n- radius: " << s.radius;
  return st;
}