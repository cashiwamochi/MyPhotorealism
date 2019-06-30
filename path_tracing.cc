#include <iostream>
#include <memory>

#include <omp.h>

#include "Vec3.hpp"
#include "Ray.hpp"
#include "Image.hpp"
#include "Camera.hpp"
#include "Hit.hpp"
#include "Sphere.hpp"
#include "Aggregate.hpp"
#include "Material.hpp"

using namespace std;


#define MAX_DEPTH 500
#define ROULETTE 0.9

Vec3 radiance(const Ray& init_ray, const Aggregate& aggregate) {
  Vec3 col;
  Vec3 throughput(1.0);
  Ray ray = init_ray;

  for(int depth = 0; depth < MAX_DEPTH; ++depth) {
    Hit res;

    if(aggregate.intersect(ray, res)) {
      Vec3 n = res.hitNormal;
      Vec3 s, t;
      orthonormalBasis(n, s, t);

      Vec3 wo_local = worldToLocal(-ray.direction, s, n, t);

#if 0
      const Sphere* sphere = (Sphere*)res.hitSphere;
      auto hitMaterial = sphere->p_material;
      auto hitLight = sphere->p_light;
#else
      auto hitMaterial = res.hitSphere->p_material;
      auto hitLight = res.hitSphere->p_light;
#endif

      col += throughput*hitLight->Le();

      Vec3 brdf;
      Vec3 wi_local;
      double pdf;
      brdf = hitMaterial->sample(wo_local, wi_local, pdf);

      double cos = cosTheta(wi_local);
      Vec3 wi = localToWorld(wi_local, s, n, t);

      throughput *= brdf*cos/pdf;

      ray = Ray(res.hitPos + 0.001*res.hitNormal, wi);
    }
    else {
      col += throughput*Vec3(1.0);
      break;
    }

    if(rnd() > ROULETTE) {
      break;
    }
    else {
      throughput /= ROULETTE;
    }
  }

  return col;
}

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
