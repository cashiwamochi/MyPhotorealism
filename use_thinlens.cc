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
#include "Sky.hpp"

using namespace std;

#define MAX_DEPTH 250
#define ROULETTE 0.9

Vec3 radiance(const Ray& init_ray, const Aggregate& aggregate, const Sky& sky) {
  Vec3 col(0.0);
  Vec3 throughput(1.0);
  Ray ray = init_ray;

  for(int depth = 0.0; depth < MAX_DEPTH; ++depth) {
    Hit res;

    if(aggregate.intersect(ray, res)) {
      Vec3 n = res.hitNormal;
      Vec3 s, t;
      orthonormalBasis(n, s, t);

      Vec3 wo_local = worldToLocal(-ray.direction, s, n, t);

      auto hitMaterial = res.hitSphere->p_material;
      auto hitLight = res.hitSphere->p_light;

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
      col += throughput * sky.getRadiance(ray);
      // col += throughput*Vec3(1.0);
      break;
    }

    if(rnd() >= ROULETTE) {
      break;
    }
    else {
      throughput /= ROULETTE;
    }
  }

  return col;
}

int main(int argc, char* argv[]) {
  const int N = 200;
  Image img(512, 512);

  // PinholeCamera cam(Vec3(0,2,1), Vec3(0,0.25,-1), 1);
  ThinLensCamera cam(Vec3(0,0,1), Vec3(0,0,-1), Vec3(0, 0, -3), 1, 0.1);

  auto mat1 = std::make_shared<Diffuse>(Vec3(0.9));
  auto mat2 = std::make_shared<Diffuse>(Vec3(0.2, 0.2, 0.8));

  auto light1 = std::make_shared<Light>(Vec3(0.0));
  // auto light2 = std::make_shared<Light>(Vec3(0.2,0.2,0.8));

  Aggregate aggregate;
  aggregate.add(std::make_shared<Sphere>(Vec3(0, -10001, 0), 10000, mat1, light1));
  aggregate.add(std::make_shared<Sphere>(Vec3(0, 0, -3), 1, mat2, light1));

  IBL sky("./../PaperMill_E_3k.hdr");

#pragma omp parallel for schedule(dynamic, 1)
  for(int r = 0; r < img.height; ++r) {
    for(int c = 0; c < img.width; ++c) {
      Vec3 col(0.0);

      for(int i = 0; i < N; ++i) {
        double u = (2.0 * (c+rnd()) - img.width)/img.width;
        double v = (2.0 * (r+rnd()) - img.height)/img.height;

        Ray ray = cam.getRay(-u, -v);
        col += radiance(ray, aggregate, sky);
      }

      img.setPixel(r, c, col/static_cast<double>(N));

#ifdef ENABLE_OPENMP
      if(omp_get_thread_num() == 0) 
#endif
        std::cout << double(c + r*img.height)/(img.width*img.height) * 100.0
                  << "\r" << std::flush;
    }
  }

  img.gammaCorrection();

  img.writePPM("use_thislens.ppm");

  return 0;
}
