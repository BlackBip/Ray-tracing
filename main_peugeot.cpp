#include <iostream>
#include <vector>
#include <memory>

#include "quad.h"
#include "material.h"
#include "shape.h"
#include "camera.h"
#include "sphere.h"
#include "scene.h"

int main() {
  Camera camera(Vector3f(-70.,0.,0.), Vector3f(1.,0.,0.), 3.14/2);

  Material m1(Color(1.,0.,0.),0.2); // plafond
  Material m2(Color(0.,1.,0.),0.2); // sol
  Material m3(Color(0.,0.,1.),0.2); // mur devant
  Material m4(Color(1.,1.,0.),0.2); // mur arrière (pour rélexion)
  Material m5(Color(1.,0.,1.),0.2); // mur droit
  Material m6(Color(0.,1.,1.),0.2); // mur gauche
  Material m7(Color(1.,1.,1.),0.8); // sphere
  Material m8(Color(1.0,1.0,1.0),0.1); // cube

  Quad ground(Vector3f(-100.,-100.,-100.), 200., 1., 200., m1);
  Quad roof(Vector3f(-100.,100.,-100.), 200., 1., 200., m2);
  Quad w1(Vector3f(100.,-100.,-100.), 1., 200., 200., m3);
  Quad w2(Vector3f(-100.,-100.,-100.), 1., 200., 200., m4);
  Quad w3(Vector3f(-100.,-100.,100.), 200., 200., 1., m5);
  Quad w4(Vector3f(-100.,-100.,-100.), 200., 200., 1., m6);
  Sphere s(Vector3f(70.,-15.,-15.), 25., m7);
  Quad cube(Vector3f(40.,50.,15.), 30., 50., 30., m8);

  Vector3f light(0.,-80.,-40.);

  int nb_shapes = 8;
  Shape** listS = new Shape*[nb_shapes];
  listS[0] = &ground;
  listS[1] = &roof;
  listS[2] = &w1;
  listS[3] = &w2;
  listS[4] = &w3;
  listS[5] = &w4;
  listS[6] = &s;
  listS[7] = &cube;


  Scene sc(camera, listS, light, nb_shapes);
  sc.render(500, 500, "test.bmp", 5, 2);

  return 0;
}