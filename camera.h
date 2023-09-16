/**
 * @file camera.h
 * @brief Defines the Camera class that represents a camera in a 3D scene.
 */

#ifndef CAMERA_H
#define CAMERA_H

#include <ostream>
#include "vector3f.h"

/**
 * @class Camera
 * @brief Represents a camera in a 3D scene.
 */
class Camera {
  public:
    /**
     * @brief The position of the camera in 3D space.
     */
    Vector3f position;
    /**
     * @brief The direction the camera is facing.
     */
    Vector3f direction;
    /**
     * @brief The field of view of the camera.
     */
    float fov;
    Camera() = default;
    /**
     * @brief Constructs a new Camera object with the given values.
     * @param position_ The position of the camera in 3D space.
     * @param direction_ The direction the camera is facing.
     * @param fov The field of view of the camera.
     * @throw runtime_error if fov is not in between 0 and pi
     */
    Camera(Vector3f position_, Vector3f direction_, float fov);
};

std::ostream & operator<< (std::ostream &st, const Camera &c);

#endif