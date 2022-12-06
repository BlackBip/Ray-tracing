#include <cmath>
#include "vector3f.h"

Vector3f::Vector3f(float x_, float y_, float z_) {
  x = x_;
  y = y_;
  z = z_;
}

Vector3f & Vector3f::operator+=(Vector3f v) {
  return *this = Vector3f(x+v.x, y+v.y, z+v.z);
}

Vector3f & Vector3f::operator-=(Vector3f v) {
  return *this += (-1.)*v;
}

Vector3f & Vector3f::operator*=(float f) {
  return *this = Vector3f(x*f, y*f, z*f);
}

Vector3f & Vector3f::operator/=(float f) {
  if (f<1e-5) {
    throw "Division by zero";
  }
  return *this *= 1./f;
}

float norm (const Vector3f &v) {
  return sqrt(pow(v.x,2)+pow(v.y,2)+pow(v.z,2));
}

float dot_product (const Vector3f &v1, const Vector3f &v2) {
  return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
}

Vector3f cross_product (const Vector3f &v1, const Vector3f &v2) {
  Vector3f v3;
  v3.x = v1.y * v2.z - v1.z * v2.y;
  v3.y = v1.z * v2.x - v1.x * v2.z;
  v3.z = v1.x * v2.y - v1.y * v2.x;
  return v3;
}

Vector3f operator+ (const Vector3f &v1, const Vector3f &v2) {
  return Vector3f(v1)+=v2;
}

Vector3f operator- (const Vector3f &v1, const Vector3f &v2) {
  return Vector3f(v1)-=v2;
}

Vector3f operator* (const float &f, const Vector3f &v) {
  return Vector3f(v)*=f;
}

Vector3f operator/ (const Vector3f &v, const float &f) {
  return Vector3f(v)/=f;
}

std::ostream & operator<< (std::ostream &st, const Vector3f &v) {
  st << "x: " << v.x << ", y: " << v.y << ", z: " << v.z;
  return st;
}