/**
 * @file vector3f.h
 * @brief Defines the Vector3f class that represents a vector in a 3D scene.
 */

#ifndef VECTOR3f_H
#define VECTOR3f_H

#include <ostream>

/**
 * @class Vector3f
 * @brief Represents a vector in a 3D scene.
 */
class Vector3f {
  public:
    /**
     * @brief The x-component of the vector.
     */
    float x;
    /**
     * @brief The y-component of the vector.
     */
    float y;
    /**
     * @brief The z-component of the vector.
     */
    float z;
    Vector3f() = default;
    /**
     * @brief Constructs a new Vector3f object with the given values.
     * @param x_ The x-component of the vector.
     * @param y_ The y-component of the vector.
     * @param z_ The z-component of the vector.
     */
    Vector3f(float x_, float y_, float z_);
    Vector3f & operator+=(Vector3f v);
    Vector3f & operator-=(Vector3f v);
    Vector3f & operator*=(float f);
    Vector3f & operator/=(float f);
};

std::ostream & operator<< (std::ostream &st, const Vector3f &v);
/**
 * @brief Computes the magnitude of a vector.
 * @param v The vector.
 * @return The norm of the vector.
 */
float norm (const Vector3f &v);
/**
 * @brief Computes the dot product of two vectors.
 * @param v1 The first vector.
 * @param v2 The second vector.
 * @return The dot product of the two vectors.
 */
float dot_product (const Vector3f &v1, const Vector3f &v2);
/**
 * @brief Computes the cross product of two vectors.
 * @param v1 The first vector.
 * @param v2 The second vector.
 * @return The cross product of the two vectors.
 */
Vector3f cross_product (const Vector3f &v1, const Vector3f &v2);


Vector3f operator+ (const Vector3f &v1, const Vector3f &v2);
Vector3f operator- (const Vector3f &v1, const Vector3f &v2);
Vector3f operator* (const float &f, const Vector3f &v);
Vector3f operator* (const Vector3f &v1, const Vector3f &v2);
Vector3f operator/ (const Vector3f &v, const float &f);

#endif