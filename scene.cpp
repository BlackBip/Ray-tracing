#include "scene.h"
#include "color.h"
#include "shape.h"
#include "vector3f.h"
#include <cmath>
#include <SDL2/SDL.h>
#include <ostream>
#include <vector>
#include <thread>

Scene::Scene(Camera camera_, Shape** shapes_, Light** lights_, int nb_shapes_, int nb_lights_) {
  if ( nb_shapes_ < 0 || nb_lights_ > 3.14 ) 
    throw std::runtime_error("nb_shapes or nb_lights is negative");
  camera = camera_;
  shapes = shapes_;
  lights = lights_;
  nb_shapes = nb_shapes_;
  nb_lights = nb_lights_;
}

void Scene::render(int width, int height, std::string filename, int max_bounces, int SSAA_factor, int nb_threads){
  Color** image = new Color*[width*SSAA_factor];
  for (int i = 0; i < (width*SSAA_factor); i++) // The image is rendered at an higher resolution to avoid pixelation if SSAA_factor!=1
    image[i] = new Color[height*SSAA_factor];
  initGrid(width, height); // Avoids computing qx, qy and p1m multiple times

  int sectionSize = (width * SSAA_factor) / nb_threads;
  std::vector<std::thread> threads;
  for (int t = 0; t < nb_threads; t++) {
    int start = t * sectionSize;
    int end = start + sectionSize;
    end = (t == (nb_threads-1)) ? (width * SSAA_factor) : end;

    threads.push_back(std::thread([&, start, end] { // Divides the render between multiple threads
      for (int i = start; i < end; i++){
        for (int j = 0; j < (height*SSAA_factor); j++){
          for (int l = 0; l < nb_lights; l++){
            Shape* last_shape = NULL;
            float light_coef = lights[l]->intensity; // Store light source relative contribution
            Ray3f incident_ray = computeIncidentRay(i, j, SSAA_factor); // Computes initial light ray "coming" from the camera 
            for(int nb_bouces = 0; nb_bouces < max_bounces; nb_bouces++) { // Limits the number of light bounces
              Ray3f reflexion;
              Shape* reflexion_shape = NULL;
              float min_dist = std::numeric_limits<float>::max();
              for (int k = 0; k < nb_shapes; k++) { // Find the first shape hit by the light ray
                if (shapes[k] != last_shape && shapes[k]->isHit(incident_ray)) {
                  Ray3f reflexion_k = shapes[k]->reflect(incident_ray);
                  float dist = norm(reflexion_k.origin-incident_ray.origin);
                  if (dist<min_dist) {
                    min_dist = dist;
                    reflexion = reflexion_k;
                    reflexion_shape = shapes[k];
              }}}
              if (reflexion_shape==NULL) // If not shapes are hit, ends the loop. This should not happen with our scenes
                nb_bouces = max_bounces;
              else {
                // Compute the color contribution of this 'bounce'
                image[i][j] += light_coef * isEnlightened(shapes, nb_shapes, lights[l]->position, reflexion.origin) * (1-reflexion_shape->matter.shininess) * reflexion_shape->matter.c;
                light_coef *= reflexion_shape->matter.shininess; // Sets the new light source relative contribution
                last_shape = reflexion_shape; // Store the hit shape to avoid light bouncing on it in the next iteration
                incident_ray = reflexion; // Sets the incident ray as the reflected one
    }}}}}}));};

  for (auto& thread : threads)
    thread.join();
  save(image, width, height, filename, SSAA_factor);

  for (int i = 0; i < width; ++i) // Cleanup
    delete [] image[i];
  delete[] image;
}

// See https://en.wikipedia.org/wiki/Ray_tracing_(graphics)#Calculate_rays_for_rectangular_viewport
// Variable names were left unchanged for code clarity
void Scene::initGrid(int width, int height) {
  Vector3f t = camera.direction/norm(camera.direction);
  Vector3f v = Vector3f(0,1,0);
  Vector3f b = cross_product(t,v);
  b /= norm(b);
  float gx = tan(camera.fov/2);
  float gy = gx*(height-1)/(width-1);
  qx = (2*gx)/(width-1)*b;
  qy = (2*gy)/(height-1)*v;
  p1m = t-gx*b-gy*v;
}

// See https://en.wikipedia.org/wiki/Ray_tracing_(graphics)#Calculate_rays_for_rectangular_viewport
// Variable names were left unchanged for code clarity
Ray3f Scene::computeIncidentRay(int i, int j, int SSAA_factor){
  return Ray3f(camera.position, p1m+(i-1)/(float)SSAA_factor*qx+(j-1)/(float)SSAA_factor*qy);
}

void save(Color **image, int width, int height, std::string filename, int SSAA_factor){
  SDL_Surface* surface = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);

  Uint32* pixels = (Uint32*)surface->pixels;
  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      Color SSAA_color = Color(0.,0.,0.);
      int x_start = i*SSAA_factor;
      int y_start = j*SSAA_factor;
      float value_of_subpixel = 1/((float)(SSAA_factor*SSAA_factor));
      for (int x = 0; x < SSAA_factor; x++) { // As we use SSAA, we need to compute an average to get each pixel color
        for (int y = 0; y < SSAA_factor; y++) {
          SSAA_color += value_of_subpixel*image[x_start+x][y_start+y];
        }
      }
      pixels[i+j*width] = SDL_MapRGB(surface->format, floatToInt(SSAA_color.r), floatToInt(SSAA_color.g), floatToInt(SSAA_color.b));
    }
  }

  if (SDL_SaveBMP(surface, filename.c_str())) {
    throw std::runtime_error("Cannot save file");
  }
}

std::ostream & operator<< (std::ostream &st, const Scene &s) {
  st << "Camera: " << s.camera << "\nNumbers of shapes: " << s.nb_shapes << "\nNumbers of lights: " << s.nb_lights;
  return st;
}