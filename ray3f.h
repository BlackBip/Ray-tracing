/**
 * @file ray3f.h
 * @brief Defines the Ray3f class that represents a light ray in a 3D scene.
 */

#ifndef RAY3f_H
#define RAY3f_H

#include <ostream>
#include "vector3f.h"

/**
 * @class Ray3f
 * @brief Represents a light ray in a 3D scene.
 */
class Ray3f {
  public:
    /**
     * @brief The origin of the light ray in 3D space.
     */
    Vector3f origin;
    /**
     * @brief The direction of the light ray in 3D space.
     */
    Vector3f direction;
    Ray3f() = default;
    /**
     * @brief Constructs a new Ray3f object with the given values.
     * @param origin_ The origin of the light ray in 3D space.
     * @param direction_ The direction of the light ray in 3D space.
     * @throw runtime_error if direction is near (0,0,0)
     */
    Ray3f(Vector3f origin_, Vector3f direction_);
};

std::ostream & operator<< (std::ostream &st, const Ray3f &r);

#endif