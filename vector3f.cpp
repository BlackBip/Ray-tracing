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