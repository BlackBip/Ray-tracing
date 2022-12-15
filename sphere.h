/**
  * @file sphere.h
  * @brief Defines the Sphere class that represents a sphere in a 3D scene.
  * @implements Shape
  */

#ifndef SPHERE_H
#define SPHERE_H

#include "vector3f.h"
#include "ray3f.h"
#include "shape.h"
#include "material.h"

/**
 * @class Sphere
 * @brief Represents a sphere in 3D space.
 */
class Sphere : public Shape {
  public:
    /**
     * @brief The origin of the sphere.
     */
    Vector3f origin;
    /**
     * @brief The radius of the sphere.
     */
    float radius;
    /**
     * @brief Indicates whether a given ray intersects this shape.
     * @param ray The ray to test for intersection.
     * @return true if the ray intersects this shape, false otherwise.
     */
    bool isHit(Ray3f ray) const;
    /**
     * @brief Computes the reflected ray when a given ray hits this shape.
     * @param ray The ray that hits this shape.
     * @return The reflected ray.
     */
    Ray3f reflect(Ray3f ray) const;
    /**
     * @brief Constructs a new Sphere object with the given values.
     * @param position_ The origin of the sphere.
     * @param radius_ The radius of the sphere.
     */
    Sphere(Vector3f origin_, float radius_, Material matter_);
    Sphere() = default;
};

std::ostream & operator<< (std::ostream &st, const Sphere &s);

#endif