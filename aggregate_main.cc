#include <iostream>
#include <memory>

#include "Vec3.hpp"
#include "Ray.hpp"
#include "Image.hpp"
#include "Camera.hpp"
#include "Hit.hpp"
#include "Sphere.hpp"
#include "Aggregate.hpp"

using namespace std;

auto main(int argc, char* argv[]) -> int 
try
{
  const int height = 512;
  const int width = 512;
  Image img(height, width);
  PinholeCamera cam(Vec3(0,0,0), Vec3(0,0,-1), 1);

  Aggregate aggregate;

  aggregate.add(std::make_shared<Sphere>(Sphere(Vec3(0.0,0.0,-3.0), 1.0)));
  aggregate.add(std::make_shared<Sphere>(Sphere(Vec3(0.0,-10001.0,-3.0), 10000.0)));

  for(int r = 0; r < img.height; ++r) {
    for(int c = 0; c < img.width; ++c) {
      double u = (2.0 * c - img.width)/img.width;
      double v = (2.0 * r - img.height)/img.height;

      Ray ray = cam.getRay(-u, -v);
      Vec3 col;
      Hit res;

      if(aggregate.intersect(ray, res)) {
        img.setPixel(r, c, res.hitNormal + 1.0/2.0);
      }
      else {
        img.setPixel(r, c, Vec3(0));
      }
    }
  }

  img.writePPM("test_aggregate.ppm");

  return 0;
}
catch(const char* e)
{
  std::cerr << e << std::endl;
  return 1;
}
