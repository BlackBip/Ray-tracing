#include "scene.h"
#include "color.h"
#include "shape.h"
#include "vector3f.h"
#include <cmath>
#include <iostream>
#include <SDL2/SDL.h>

Scene::Scene(Camera camera_, Shape** shapes_, Vector3f source_, int nb_shapes_) {
  camera = camera_;
  shapes = shapes_;
  source = source_;
  nb_shapes = nb_shapes_;
}

void Scene::render(int width, int height, std::string filename, int bounces){
  Shape* lastShape = NULL;
  Color** image = new Color*[height];
  for (int i = 0; i < width; ++i)
    image[i] = new Color[width];
    
  for (int i = 0; i < width; i++){
    for (int j = 0; j < height; j++){
      Shape* lastShape = NULL;
      float coef = 1.;
      Ray3f ray = computeVect(i, j, width, height);
      for(int _ = 0; _ < bounces; _++) {
        Ray3f* reflexions = new Ray3f[nb_shapes];
        Shape** hit = new Shape*[nb_shapes];
        int reflexion_size = 0;
        for (int k = 0; k < nb_shapes; k++) {
          if (shapes[k] != lastShape && shapes[k]->isHit(ray)) {
            hit[reflexion_size] = shapes[k];
            reflexions[reflexion_size] = shapes[k]->reflect(ray);
            reflexion_size++;
          }
        }
        if (reflexion_size==0) {
          _ = bounces;
        }
        else {
          Ray3f reflexion = reflexions[0];
          Shape* closest_shape = hit[0];
          float min_dist = norm(reflexion.origin-ray.origin);
          for(int k=1; k<reflexion_size; k++) {
            float dist = norm(reflexions[k].origin-ray.origin);
            if (dist<min_dist) {
              min_dist = dist;
              reflexion = reflexions[k];
              closest_shape = hit[k];          
            }
          }
          delete [] hit;
          image[i][j] += coef * isEnlightened(shapes, nb_shapes, lastShape, source, reflexion.origin) * (1-closest_shape->matter.shininess) * closest_shape->matter.c;
          coef *= closest_shape->matter.shininess;
          lastShape = closest_shape;
          ray = reflexion;
        }
      }
    }
    save(image, width, height);

  } 
}

Ray3f Scene::computeVect(int i, int j, int width, int height){
  Vector3f t = camera.direction/norm(camera.direction);
  Vector3f v = Vector3f(0,1,0); // à revoir
  Vector3f b = Vector3f(0,0,1);
  float gx = tan(camera.fov/2); // aussi
  float gy = gx*(height-1)/(width-1);
  Vector3f qx = (2*gx)/(width-1)*b;
  Vector3f qy = (2*gy)/(height-1)*v;
  Vector3f p1m = t-gx*b-gy*v;
  return Ray3f(camera.position, p1m+(i-1)*qx+(j-1)*qy);
}

void save(Color **image, int width, int height){
  SDL_Surface* surface = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);

  Uint32* pixels = (Uint32*)surface->pixels;
  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      pixels[i+j*width] = SDL_MapRGB(surface->format, floatToInt(image[i][j].r), floatToInt(image[i][j].g), floatToInt(image[i][j].b));
    }
  }

  if (SDL_SaveBMP(surface, "test.bmp")) {
    throw "Cannot save file";
  }
}

std::ostream & operator<< (std::ostream &st, const Scene &s) {
  st << "Camera: " << s.camera << "\nShape: " << s.shapes << "\nNumbers of shapes: " << s.nb_shapes << "\nSource: " << s.source;
  return st;
}