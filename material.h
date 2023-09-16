/**
 * @file material.h
 * @brief Defines the Material class that represents a material for ray tracing.
 */

#ifndef MATERIAL_H
#define MATERIAL_H

#include <ostream>
#include "color.h"

/**
 * @class Material
 * @brief Represents material for ray tracing.
 */
class Material {
  public:
    /**
     * @brief The color of the material.
     */
    Color c;
    /**
     * @brief The shininess of the material.
     */
    float shininess;
    /**
     * @brief Constructs a new Material object with the given values.
     * @param c_ The color of the material.
     * @param shininess_ The shininess of the material.
     * @throw runtime_error if shininess is not between 0 and 1
     */
    Material(Color c_, float shininess_);
    Material() = default;
};

std::ostream & operator<< (std::ostream &st, const Material &m);

#endif