#include "scene.h"
#include "color.h"
#include "shape.h"
#include "vector3f.h"
#include <cmath>
#include <SDL2/SDL.h>
#include <iostream>

Scene::Scene(Camera camera_, Shape** shapes_, Vector3f source_, int nb_shapes_) {
  camera = camera_;
  shapes = shapes_;
  source = source_;
  nb_shapes = nb_shapes_;
}

void Scene::render(int width, int height, std::string filename, int bounces, int SSAA){
  Shape* lastShape = NULL;
  Color** image = new Color*[height*SSAA];
  for (int i = 0; i < (height*SSAA); i++) //?
    image[i] = new Color[width*SSAA];
  initGrid(width, height);
    
  for (int i = 0; i < (width*SSAA); i++){
    for (int j = 0; j < (height*SSAA); j++){
      Shape* lastShape = NULL;
      float coef = 1.;
      Ray3f ray = computeVect(i, j, SSAA);
      for(int nb_bouces = 0; nb_bouces < bounces; nb_bouces++) {
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
        if (reflexion_size==0)
          nb_bouces = bounces;
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
          image[i][j] += coef * isEnlightened(shapes, nb_shapes, source, reflexion.origin) * (1-closest_shape->matter.shininess) * closest_shape->matter.c;
          coef *= closest_shape->matter.shininess;
          lastShape = closest_shape;
          ray = reflexion;
        }
      }
    }
  }

  save(image, width, height, filename, SSAA);

  for (int i = 0; i < width; ++i)
    delete [] image[i];
  delete[] image;
}

void Scene::initGrid(int width, int height) {
  Vector3f t = camera.direction/norm(camera.direction);
  Vector3f v = Vector3f(0,1,0); // à fix pour tourner la cam
  Vector3f b = Vector3f(0,0,1);
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
    throw "Cannot save file";
  }
}

std::ostream & operator<< (std::ostream &st, const Scene &s) {
  st << "Camera: " << s.camera << "\nShape: " << s.shapes << "\nNumbers of shapes: " << s.nb_shapes << "\nSource: " << s.source;
  return st;
}