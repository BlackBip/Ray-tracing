/**
 * @file shape.h
 * @brief Defines the Shape abstract class that represents a geometric shape in a 3D scene.
 */

#ifndef SHAPE_H
#define SHAPE_H

#include "vector3f.h"
#include "ray3f.h"
#include "material.h"

/**
 * @class Shininess
 * @brief Represents a geometric shape in a 3D scene.
 */
class Shape {
  public:
    /**
     * @brief The material the shape is made of.
     */
    Material matter;
    /**
     * @brief Indicates whether a given ray intersects this shape.
     *  @param ray The ray to test for intersection.
     * @return true if the ray intersects this shape, false otherwise.
     */
    virtual bool isHit(Ray3f ray) const = 0; 
    /**
     * @brief Computes the reflected ray when a given ray hits this shape.
     * @param ray The ray that hits this shape.
     * @return The reflected ray.
     */
    virtual Ray3f reflect(Ray3f ray) const = 0;
};

/**
 * @brief Determines whether a given point is illuminated by a light source.
 * @param shapes An array of shapes in the scene.
 * @param nb_shapes The number of shapes in the array.
 * @param light The position of the light source.
 * @param point The point to test for illumination.
 * @return true if the point is illuminated by the light source, false otherwise.
 */
bool isEnlightened(Shape** shapes, int nb_shapes, Vector3f light, Vector3f point);

#endif