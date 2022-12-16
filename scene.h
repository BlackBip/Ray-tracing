/**
* @file scene.h
* @brief Defines the Scene class that represents a 3D scene to be rendered.
 */

#ifndef SCENE_H
#define SCENE_H

#include <ostream>
#include <string>

#include "shape.h"
#include "camera.h"
#include "ray3f.h"
#include "light.h"

/**
 * @class Scene
 * @brief Represents a 3D scene to be rendered.
 */
class Scene {
  private:
    /**
     * @brief Computes the incident ray at a given pixel.
     * @param i The x-coordinate of the pixel.
     * @param j The y-coordinate of the pixel.
     * @param SSAA_factor The super-sampling factor.
     * @return The incident ray at the given pixel.
     */
    Ray3f computeIncidentRay(int i, int j, int SSAA_factor);
    /**
     * @brief Initializes the grid of pixels in the image by computing qx, qy and p1m.
     * @param width The width of the image.
     * @param height The height of the image.
     * @see https://en.wikipedia.org/wiki/Ray_tracing_(graphics)#Calculate_rays_for_rectangular_viewport
     */
    void initGrid(int width, int height);
    /**
     * @brief The x-component of the coordinate basis of the image plane.
     * @see https://en.wikipedia.org/wiki/Ray_tracing_(graphics)#Calculate_rays_for_rectangular_viewport
     */
    Vector3f qx;
    /**
     * @brief The y-component of the coordinate basis of the image plane.
     * @see https://en.wikipedia.org/wiki/Ray_tracing_(graphics)#Calculate_rays_for_rectangular_viewport
     */
    Vector3f qy;
    /**
     * @brief  The lower-left corner of the image plane.
     * @see https://en.wikipedia.org/wiki/Ray_tracing_(graphics)#Calculate_rays_for_rectangular_viewport
     */
    Vector3f p1m;
  public:
    /**
     * @brief The camera used to capture the scene.
     */
    Camera camera;
    /**
     * @brief The shapes in the scene.
     */
    Shape** shapes;
    /**
     * @brief The lights in the scene.
     */
    Light** lights;
    /**
     * @brief The number of shapes in the scene.
     */
    int nb_shapes;
    /**
     * @brief The number of lights in the scene.
     */
    int nb_lights;
    /**
     * @brief Constructs a new Scene object.
     * @param camera_ The camera used to capture the scene.
     * @param shapes_ The shapes in the scene.
     * @param lights_ The lights in the scene.
     * @param nb_shapes_ The number of shapes in the scene.
     * @param nb_lights_ The number of lights in the scene.
     * @throw runtime_error if nb_shapes or nb_lights is negative
     */
    Scene(Camera camera_, Shape** shapes_, Light** lights_, int nb_shapes_, int nb_lights_);
    /**
     * @brief Renders the scene to an image.
     * @param width The width of the image to be generated.
     * @param height The height of the image to be generated.
     * @param filename The name of the file to save the image to.
     * @param max_bounces The maximum number of bounces of light to simulate.
     * @param SSAA_factor The super-sampling factor.
     * @param nb_threads The number of threads to use for rendering.
     */
    void render(int width, int height, std::string filename, int max_bounces, int SSAA_factor=1, int nb_threads=1);
};

std::ostream & operator<< (std::ostream &st, const Scene &s);
/**
 * @brief Saves the given image to a bmp file named filename using the SDL.
 * @param image The image to save.
 * @param width The width of the image.
 * @param height The height of the image.
 * @param filename The name of the file to save the image to.
 * @throw runtime_error if we cannot save file
 */
void save(Color **image, int width, int height, std::string filename, int SSAA);

#endif