#include "scene.h"
#include "color.h"
#include "shape.h"
#include "vector3f.h"
#include <cmath>
#include <SDL2/SDL.h>
#include <ostream>
#include <vector>
#include <thread>

Scene::Scene(Camera camera_, Shape** shapes_, Vector3f source_, int nb_shapes_) {
  camera = camera_;
  shapes = shapes_;
  source = source_;
  nb_shapes = nb_shapes_;
}

void Scene::render(int width, int height, std::string filename, int bounces, int SSAA, int numThreads){
  Shape* lastShape = NULL;
  Color** image = new Color*[height*SSAA];
  for (int i = 0; i < (height*SSAA); i++) //?
    image[i] = new Color[width*SSAA];
  initGrid(width, height);

  int sectionSize = (width * SSAA) / numThreads;

  std::vector<std::thread> threads;
  for (int t = 0; t < numThreads; t++) {
    int start = t * sectionSize;
    int end = start + sectionSize;

    threads.push_back(std::thread([&, start, end] {
      for (int i = start; i < end; i++){
        for (int j = 0; j < (height*SSAA); j++){
          Shape* lastShape = NULL;
          float coef = 1.;
          Ray3f ray = computeVect(i, j, SSAA);
          for(int nb_bouces = 0; nb_bouces < bounces; nb_bouces++) {
            Ray3f reflexion;
            Shape* reflexion_shape = NULL;
            float min_dist = std::numeric_limits<float>::max();
            for (int k = 0; k < nb_shapes; k++) {
              if (shapes[k] != lastShape && shapes[k]->isHit(ray)) {
                Ray3f reflexion_k = shapes[k]->reflect(ray);
                float dist = norm(reflexion_k.origin-ray.origin);
                if (dist<min_dist) {
                  min_dist = dist;
                  reflexion = reflexion_k;
                  reflexion_shape = shapes[k];
                }
              }
            }
            if (reflexion_shape==NULL)
              nb_bouces = bounces;
            else {
              image[i][j] += coef * isEnlightened(shapes, nb_shapes, source, reflexion.origin) * (1-reflexion_shape->matter.shininess) * reflexion_shape->matter.c;
              coef *= reflexion_shape->matter.shininess;
              lastShape = reflexion_shape;
              ray = reflexion;
            }
          }
        }
      }
    }));
  }

  for (auto& thread : threads) {
    thread.join();
  }

  save(image, width, height, filename, SSAA);

  for (int i = 0; i < width; ++i)
    delete [] image[i];
  delete[] image;
}


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

Ray3f Scene::computeVect(int i, int j, int SSAA){
  return Ray3f(camera.position, p1m+(i-1)/(float)SSAA*qx+(j-1)/(float)SSAA*qy);
}

void save(Color **image, int width, int height, std::string filename, int SSAA){
  SDL_Surface* surface = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);

  Uint32* pixels = (Uint32*)surface->pixels;
  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      Color SSAAcolor = Color(0.,0.,0.);
      int x_start = i*SSAA;
      int y_start = j*SSAA;
      float value_of_subpixel = 1/((float)(SSAA*SSAA));
      for (int x = 0; x < SSAA; x++) {
        for (int y = 0; y < SSAA; y++) {
          SSAAcolor += value_of_subpixel*image[x_start+x][y_start+y];
        }
      }
      pixels[i+j*width] = SDL_MapRGB(surface->format, floatToInt(SSAAcolor.r), floatToInt(SSAAcolor.g), floatToInt(SSAAcolor.b));
    }
  }

  if (SDL_SaveBMP(surface, filename.c_str())) {
    throw std::runtime_error("Cannot save file");
  }
}

std::ostream & operator<< (std::ostream &st, const Scene &s) {
  st << "Camera: " << s.camera << "\nShape: " << s.shapes << "\nNumbers of shapes: " << s.nb_shapes << "\nSource: " << s.source;
  return st;
}