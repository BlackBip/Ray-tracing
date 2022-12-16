/**
 * @file light.h
 * @brief Defines the Light class that represents a light source in a 3D scene.
 */

#ifndef LIGHT_H
#define LIGHT_H

#include <ostream>
#include "vector3f.h"

/**
 * @class Light
 * @brief Represents a light source in a 3D scene.
 */
class Light {
  public:
    /**
     * @brief The position of the light source in 3D space.
     */
    Vector3f position;
    /**
     * @brief The intensity of the light source.
     */
    float intensity;
    Light() = default;
    /**
     * @brief Constructs a new Light object with the given values.
     * @param position_ The position of the light source in 3D space.
     * @param intensity_ The intensity of the light source.
     * @throw runtime_error if intensity is not between 0 and 1
     */
    Light(Vector3f position_, float intensity_);
};

std::ostream & operator<< (std::ostream &st, const Light &l);

#endif