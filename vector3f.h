#ifndef VECTOR3f_H
#define VECTOR3f_H

#include <ostream>

class Vector3f {
  public:
    float x;
    float y;
    float z;
    Vector3f() = default; // c'est porteur ça mais pourquoi c'est une bonne question
    Vector3f(float x_, float y_, float z_);
    Vector3f & operator+=(Vector3f v);
    Vector3f & operator-=(Vector3f v);
    Vector3f & operator*=(float f);
    Vector3f & operator/=(float f);
};

std::ostream & operator<< (std::ostream &st, const Vector3f &v);
float norm (const Vector3f &v);
float dot_product (const Vector3f &v1, const Vector3f &v2);

Vector3f operator+ (const Vector3f &v1, const Vector3f &v2);
Vector3f operator- (const Vector3f &v1, const Vector3f &v2);
Vector3f operator* (const float &f, const Vector3f &v);
Vector3f operator/ (const Vector3f &v, const float &f);

#endif