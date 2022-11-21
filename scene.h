#ifndef SCENE_H
#define SCENE_H

#include <ostream>
#include <string>
#include "shape.h"
#include "camera.h"
#include "ray3f.h"

class Scene {
  public:
    Camera camera;
    Shape** shapes;
    Ray3f source;
    int nb_shapes;
    Scene(Camera camera_, Shape** shapes_, Ray3f source_,int nb_shapes);
    void render(int width, int height, std::string filename);
};

std::ostream & operator<< (std::ostream &st, const Scene &s);
void save(Color **image, int width, int height);

#endif