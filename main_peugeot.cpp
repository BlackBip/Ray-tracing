#include <iostream>
#include <vector>
#include <memory>

#include "quad.h"
#include "material.h"
#include "shape.h"
#include "camera.h"
#include "scene.h"

int main() {
  Camera camera(Vector3f(0.,0.,0.), Vector3f(1.,0.,0.), 3.14/2.);

  Material m1(Color(0.5,0.5,0.5),1.);
  Quad ground(Vector3f(-1000.,-1000.,-1000.), Vector3f(2000.,0.,0.), Vector3f(0.,1.,0.), Vector3f(0.,0.,2000.), m1);
  Quad roof(Vector3f(-1000.,1000.,-1000.), Vector3f(2000.,0.,0.), Vector3f(0.,1.,0.), Vector3f(0.,0.,2000.), m1);
  Quad w1(Vector3f(1000.,-1000.,-1000.), Vector3f(1.,0.,0.), Vector3f(0.,2000.,0.), Vector3f(0.,0.,2000.), m1);
  Quad w2(Vector3f(-1000.,-1000.,-1000.), Vector3f(1.,0.,0.), Vector3f(0.,2000.,0.), Vector3f(0.,0.,2000.), m1);
  Quad w3(Vector3f(-1000.,-1000.,1000.), Vector3f(2000.,0.,0.), Vector3f(0.,2000.,0.), Vector3f(0.,0.,1.), m1);
  Quad w4(Vector3f(-1000.,-1000.,-1000.), Vector3f(2000.,0.,0.), Vector3f(0.,2000.,0.), Vector3f(0.,0.,1.), m1);
  Vector3f light(0.,800.,0.);
  int nb_shapes = 6;
  Shape** listS = new Shape*[nb_shapes];
  listS[0] = &ground;
  listS[1] = &roof;
  listS[2] = &w1;
  listS[3] = &w2;
  listS[4] = &w3;
  listS[5] = &w4;
  Scene sc(camera, listS, light, nb_shapes);
  sc.render(10, 10, "test", 1);

  return 0;
}