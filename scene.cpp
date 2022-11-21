#include "scene.h"
#include "color.h"
#include "shape.h"
#include "vector3f.h"

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

std::ostream & operator<< (std::ostream &st, const Scene &s) {
  st << "Camera: " << s.camera << "\nShape: " << s.shapes << "\nNumbers of shapes: " << s.nb_shapes << "\nSource: " << s.source;
  return st;
}