#include "scene.h"

Scene::Scene(Camera camera_, Shape* shapes_, Ray3f source_) {
  camera = camera_;
  shapes = shapes_;
  source = source_;
}

void render(int width, int height, std::string filename){
    //TODO
}

std::ostream & operator<< (std::ostream &st, const Scene &s) {
  st << "Camera: " << s.camera << "\nShape: " << s.shapes << "\nSource: " << s.source;
  return st;
}