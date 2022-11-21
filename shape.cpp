#include "shape.h"

bool isEnlightened(Shape** shapes, int nb_shapes, Shape* last_shape, Vector3f light, Vector3f point){
  float light_dist = norm(light - point);
  for (int i = 0; i < nb_shapes; i++) {
    if (last_shape != shapes[i]) {
      Ray3f light_path(light, point-light);
      if (shapes[i]->isHit(light_path)) {
        Vector3f potential_obstacle = shapes[i]->reflect(light_path).origin;
        if (light_dist > norm(light - potential_obstacle)) {
          return false;
        }
      }
    }
  }
  return true;
}