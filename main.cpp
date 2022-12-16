#include <thread>
#include <iostream>

#include "shape.h"
#include "quad.h"
#include "sphere.h"
#include "scene.h"
#include "material.h"
#include "camera.h"
#include "light.h"

/**
 * @file main.c
 * @brief Main entry point for the program.
 * This file contains the main function of the program, which accepts arguments
 * from the command line and sets the number of threads to use for rendering.
 * It also creates the objects in the scene, such as the shapes and lights,
 * and then renders the scene using the specified number of threads.
 */
int main(int argc, char* argv[]) {

  bool render_all = false;
  int thread_count = 0;

  // Arguments checks, behavior switch and thread_count setting

  for (int i=1; i<argc; i++) {
    if (std::string(argv[i]) == "--help") {
      std::cout << "Usage: program_name [--render-all] [--threads n]\n"
                << "This program accepts an optional --render-all flag that will generate the report .bmp image.\n"
                << "If not used, a single image will be displayed in a window.\n"
                << "This program accepts an optional --threads flag followed by an integer value.\n"
                << "If not used, the program will try to use the all the threads available.\n";
      return 0;
    }
    else if (std::string(argv[i]) == "--threads") {
      if (argc < (i+1)) {
        std::cout << "Error: invalid value for --thread.\n"
                  << "Use --help for usage information.\n";
        return 1;
      }
      thread_count = std::atoi(argv[i+1]);
      i++;
      if (thread_count == 0) {
        std::cout << "Error: invalid value for --thread.\n"
                  << "Use --help for usage information.\n";
        return 1;
      }
      else {
        std::cout << "Using " << thread_count << " threads.\n";
      }
    }
    else if (std::string(argv[i]) == "--render-all") {
      render_all = true;
    }
    else {
      std::cout << "Error: invalid argument provided.\n"
                << "Use --help for usage information.\n";
      return 1;
    }
  }
  if (thread_count == 0) {
    thread_count = std::thread::hardware_concurrency();
    if (thread_count!=0) {
       std::cout << "--threads unused, using the maximum number of threads (" << thread_count << ")\n";
    }
    else {
      std::cout << "--threads unused and unable to determine the number of threads. Using 1 thread.\n";
      thread_count = 1;
    }
  }

  // Scenes shapes

  Material ceiling_material(Color(1.,0.,0.),0.2);
  Quad ceiling(Vector3f(-100.,-100.,-100.), 200., 1., 200., ceiling_material);

  Material ground_material(Color(0.,1.,0.),0.2);
  Quad ground(Vector3f(-100.,100.,-100.), 200., 1., 200., ground_material);

  Material front_wall_material(Color(0.,0.,1.),0.2);
  Quad front_wall(Vector3f(100.,-100.,-100.), 1., 200., 200., front_wall_material);

  Material back_wall_material(Color(1.,1.,0.),0.2);
  Quad back_wall(Vector3f(-100.,-100.,-100.), 1., 200., 200., back_wall_material);

  Material right_wall_material(Color(1.,0.,1.),0.2);
  Quad right_wall(Vector3f(-100.,-100.,100.), 200., 200., 1., right_wall_material);

  Material left_wall_material(Color(0.,1.,1.),0.2);
  Quad left_wall(Vector3f(-100.,-100.,-100.), 200., 200., 1., left_wall_material);

  Material sphere_material(Color(1.,1.,1.),0.8);
  Sphere sphere(Vector3f(70.,-15.,-15.), 25., sphere_material);

  Material cube_material(Color(1.0,1.0,1.0),0.1);
  Quad cube(Vector3f(40.,50.,15.), 30., 50., 30., cube_material);

  int nb_shapes = 8;
  Shape** shapes_list = new Shape*[nb_shapes] {
      &ceiling, &ground, &front_wall, &back_wall, &right_wall, &left_wall, &sphere, &cube
  };

  // Scenes lights

  Light single_light(Vector3f(0.,-80.,-40.),1.0);
  Light** single_light_list = new Light*[1] {
      &single_light
  };
  int single_light_list_size = 1;

  Light light_one(Vector3f(0.,-80.,-40.),0.7);
  Light light_two(Vector3f(50.,-80.,40.),0.3);
  Light** two_lights_list = new Light*[2] {
      &light_one, &light_two
  };
  int two_lights_list_size = 2;

  // Scenes cameras

  Camera camera_1(Vector3f(-70.,0.,0.), Vector3f(1.,0.,0.), 3.14/2);
  Camera camera_1_wide_angle(Vector3f(-70.,0.,0.), Vector3f(1.,0.,0.), 130. * 3.14/180.);
  Camera camera_2(Vector3f(-60.,99.,-60.), Vector3f(1.,-0.8,1.), 3.14/2);

  // Scenes

  Scene scene_camera_1_one_light(camera_1, shapes_list, single_light_list, nb_shapes, single_light_list_size);
  Scene scene_camera_1_two_lights(camera_1, shapes_list, two_lights_list, nb_shapes, two_lights_list_size);
  Scene scene_camera_1_wide_angle_two_lights(camera_1_wide_angle, shapes_list, two_lights_list, nb_shapes, two_lights_list_size);
  Scene scene_camera_2_two_lights(camera_2, shapes_list, two_lights_list, nb_shapes, two_lights_list_size);

  std::cout << "Beginning of rendering ..." << std::endl;

  if (render_all) { // Renders scene and save them in bmp files

    std::cout << "Straight camera angle, 1 light source, 0 light bounce (image 1/7)" << std::endl;
    save(scene_camera_1_one_light.render(500, 500, 1, 1, thread_count),"render_straight_angle_1_light_0_bounce.bmp");

    std::cout << "Straight camera angle, 1 light source, 1 light bounce (image 2/7)" << std::endl;
    save(scene_camera_1_one_light.render(500, 500, 2, 1, thread_count), "render_straight_angle_1_light_1_bounce.bmp");

    std::cout << "Straight camera angle, 1 light source, 5 light bounces (image 3/7)" << std::endl;
    save(scene_camera_1_one_light.render(500, 500, 6, 1, thread_count), "render_straight_angle_1_light_5_bounces.bmp");

    std::cout << "Straight camera angle, 1 light source, 5 light bounces, SSAA factor of 2 (image 4/7)" << std::endl;
    save(scene_camera_1_one_light.render(500, 500, 6, 2, thread_count), "render_straight_angle_1_light_5_bounces_2_SSAA.bmp");

    std::cout << "Straight camera angle, 2 light sources, 5 light bounces, SSAA factor of 2 (image 5/7)" << std::endl;
    save(scene_camera_1_two_lights.render(500, 500, 6, 2, thread_count), "render_straight_angle_2_lights_5_bounces_2_SSAA.bmp");

    std::cout << "Straight camera angle, 2 light sources, 5 light bounces, SSAA factor of 2, wide angle FOV (130°) (image 6/7)" << std::endl;
    save(scene_camera_1_wide_angle_two_lights.render(500, 500, 6, 2, thread_count), "render_straight_angle_2_lights_5_bounces_2_SSAA_130_fov.bmp");

    std::cout << "Low-angle shot, 2 light sources, 5 light bounces, SSAA factor of 2, 4/3 aspect ratio (image 7/7)" << std::endl;
    save(scene_camera_2_two_lights.render(666, 500, 6, 2, thread_count), "render_low_angle_2_lights_5_bounces_2_SSAA_aspect_ratio.bmp");

  }
  else { // Display one scene
    std::cout << "Straight camera angle, 2 light sources, 5 light bounces, SSAA factor of 2" << std::endl;
    display(scene_camera_1_two_lights.render(500, 500, 6, 2, thread_count), "Ray tracing project");
  }

  return 0;
}