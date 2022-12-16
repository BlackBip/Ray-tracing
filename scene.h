/**
* @file scene.h
* @brief Defines the Scene class that represents a 3D scene to be rendered.
 */

#ifndef SCENE_H
#define SCENE_H

#include <ostream>
#include <string>
#include <SDL2/SDL.h>

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
     */
    Scene(Camera camera_, Shape** shapes_, Light** lights_, int nb_shapes_, int nb_lights_);
    /**
     * @brief Renders the scene to an image using ray tracing.
     * @param width The width of the image to be generated.
     * @param height The height of the image to be generated.
     * @param max_bounces The maximum number of bounces of light to simulate.
     * @param SSAA_factor The super-sampling factor.
     * @param nb_threads The number of threads to use for rendering.
     * @return SDL_Surface* containing the image.
     */
    SDL_Surface* render(int width, int height, int max_bounces, int SSAA_factor=1, int nb_threads=1);
};

std::ostream & operator<< (std::ostream &st, const Scene &s);
/**
 * @brief Tranform the Color** image into a SDL_Surface to make it easier to save and display
 * @param image The image to save.
 * @param width The width of the image.
 * @param height The height of the image.
 * @param SSAA_factor The super-sampling factor.
 * @return SDL_Surface* containing the image.
 */
SDL_Surface* computeSDLSurface(Color **image, int width, int height, int SSAA_factor);

/**
 * @brief Saves the given surface to a bmp file named filename using the SDL.
 * @param surface The surface containing the image to save.
 * @param filename The name of the file to save the image to.
 */
void save(SDL_Surface* surface, std::string filename);

/**
 * @brief Display the surface in a winow named title using the SDL.
 * @param surface The surface containing the image to diplay.
 * @param filename The name of the SDL window.
 */
void display(SDL_Surface* surface, std::string title);

#endif