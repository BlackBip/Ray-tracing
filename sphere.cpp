#include <cmath>
#include "sphere.h"

Sphere::Sphere(Vector3f origin_, float radius_, Material matter_) {
  if (radius_<0) {
    throw "Negative radius";
  }
  origin = origin_;
  radius = radius_;
  matter = matter_;
}

// https://en.wikipedia.org/wiki/Line%E2%80%93sphere_intersection
bool Sphere::isHit(Ray3f ray) const {
  Vector3f o = ray.origin;
  Vector3f u_hat = ray.direction/norm(ray.direction);
  Vector3f c = origin;
  float r = radius;
  float delta = pow(dot_product(u_hat,o-c),2) - (pow(norm(o-c),2)+pow(r,2));
  return delta>0; // voir pour mettre un 1e-3 ou quoi
}

// https://en.wikipedia.org/wiki/Line%E2%80%93sphere_intersection
// http://www.3dkingdoms.com/weekly/weekly.php?a=2
Ray3f Sphere::reflect(Ray3f ray) const {
  Vector3f o = ray.origin;
  Vector3f u_hat = ray.direction/norm(ray.direction);
  Vector3f c = origin;
  float r = radius;
  float delta = pow(dot_product(u_hat,o-c),2) - (pow(norm(o-c),2)+pow(r,2));
  float d1 = -dot_product(u_hat,o-c)+sqrt(delta);
  float d2 = -dot_product(u_hat,o-c)-sqrt(delta);
  Vector3f intersection;
  if (abs(d1)<abs(d2)) {
    intersection = o + d1*u_hat;
  }
  else {
    intersection = o + d2*u_hat;
  }
  Vector3f N = c - intersection;
  return Ray3f(intersection, -2*dot_product(u_hat, N)*N+u_hat);
}

std::ostream & operator<< (std::ostream &st, const Sphere &s) {
  st << "Sphere: " << "\n- matter: "  << s.matter << "\n- origin: " << s.origin << "\n- radius: " << s.radius;
  return st;
}