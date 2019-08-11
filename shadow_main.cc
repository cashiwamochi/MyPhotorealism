#include <iostream>
#include <memory>

#ifdef ENABLE_OPENMP
#include <omp.h>
#endif

#include "Vec3.hpp"
#include "Ray.hpp"
#include "Image.hpp"
#include "Camera.hpp"
#include "Hit.hpp"
#include "Sphere.hpp"
#include "Aggregate.hpp"
#include "Material.hpp"

using namespace std;

auto main(int argc, char* argv[]) -> int 
try
{
  const int height = 512;
  const int width = 512;

  const int N = 100;

  Image img(height, width);
  PinholeCamera cam(Vec3(0,0,0), Vec3(0,0,-1), 1);

  Aggregate aggregate;

  aggregate.add(std::make_shared<Sphere>(Sphere(Vec3(0.0,0.0,-3.0), 1.0)));
  aggregate.add(std::make_shared<Sphere>(Sphere(Vec3(0.0,-10001.0,-3.0), 10000.0)));

  Vec3 sun_direction = normalize(Vec3(1.0,1.0,1.0));

#pragma omp parallel for schedule(dynamic, 1)
  for(int r = 0; r < img.height; ++r) {
    for(int c = 0; c < img.width; ++c) {
      Vec3 col(0.0);
      for(int i = 0; i < N; ++i) {
        double u = (2.0 * (c+rnd()) - img.width)/img.width;
        double v = (2.0 * (r+rnd()) - img.height)/img.height;

        Ray ray = cam.getRay(-u, -v);
        Hit res;

        if(aggregate.intersect(ray, res)) {
          Ray shadowRay(res.hitPos + 0.0001*res.hitNormal, sun_direction);
          Hit res_temp;
          if(!aggregate.intersect(shadowRay, res_temp)) {
            col += std::max(dot(res.hitNormal, sun_direction), 0.0) * Vec3(1.0);  
          }
        }
      }
      col /= (float)N;
      img.setPixel(r, c, col);
    }
  }

  img.writePPM("test_shadow.ppm");

  return 0;
}
catch(const char* e)
{
  std::cerr << e << std::endl;
  return 1;
}
