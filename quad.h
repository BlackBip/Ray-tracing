/**
  * @file sphere.h
  * @brief Defines the Rectangular cuboid class that represents a sphere in a 3D scene.
  * @implements Shape
  */

#ifndef QUAD_H
#define QUAD_H

#include "vector3f.h"
#include "ray3f.h"
#include "shape.h"
#include "material.h"

/**
 * @class Quad
 * @brief Represents a rectangular cuboid in 3D space.
 */
class Quad : public Shape {
  public:
    /**
     * @brief Constructs a new Quad object with the given values.
     * @param origin_ The origin of the rectangular cuboid.
     * @param width_ The width of the rectangular cuboid.
     * @param height_ The height of the rectangular cuboid.
     * @param length_ The length of the rectangular cuboid.
     */
    Quad(Vector3f origin_, float width_, float height_, float length_, Material matter_);
    /**
     * @brief The origin of the rectangular cuboid.
     */
    Vector3f origin;
    /**
     * @brief The corner of the rectangular cuboid opposite to the origin.
     */
    Vector3f top_corner;
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
};

std::ostream & operator<< (std::ostream &st, const Quad &q);

#endif