#include "scene.h"
#include "color.h"
#include "shape.h"
#include "vector3f.h"
#include <SDL2/SDL.h>

Scene::Scene(Camera camera_, Shape** shapes_, Ray3f source_, int nb_shapes_) {
  camera = camera_;
  shapes = shapes_;
  source = source_;
  nb_shapes = nb_shapes_;
}

void Scene::render(int width, int height, std::string filename){
  // On considere un pixel comme etant un carre d unite 1
  Shape* lastShape = NULL;
  Color** image = new Color*[height];
  for (int i = 0; i < width; ++i)
    image[i] = new Color[width];
  for (int i = 0; i < width; i++){
    for (int j = 0; j < height; j++){
        //
    }
  }
  
}

Vector3f computeVect(int i, int j){
  // Calcule 
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