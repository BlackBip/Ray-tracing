#ifndef SCENE_H
#define SCENE_H

#include <ostream>
#include <string>
#include "shape.h"
#include "camera.h"
#include "ray3f.h"

class Scene {
  private:
    Ray3f computeVect(int i, int j, int width, int height);
  public:
    Camera camera;
    Shape** shapes;
    Vector3f source;
    int nb_shapes;
    Scene(Camera camera_, Shape** shapes_, Vector3f source_, int nb_shapes);
    void render(int width, int height, std::string filename, int bounces);
};

std::ostream & operator<< (std::ostream &st, const Scene &s);
void save(Color **image, int width, int height);

#endif