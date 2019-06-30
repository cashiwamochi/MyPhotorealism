#pragma once

#include <cmath>
#include "Vec3.hpp"
#include "Ray.hpp"
#include "Hit.hpp"
#include "Material.hpp"
#include "Light.hpp"

class Sphere : public Hitable{
  public:
    Vec3 center;
    double radius;
    
    Sphere(const Vec3& _center, const double& _radius) {
      center = _center;
      radius = _radius;
    }

    bool intersect(const Ray& ray, Hit& res) const {
      double a = ray.direction.length2();
      double b = dot(ray.direction, ray.origin-center);
      double c = (ray.origin - center).length2() - radius*radius;

      double D = b*b - a*c;
      if(D < 0.0) return false;

      double t1 = -b - std::sqrt(D);
      double t2 = -b + std::sqrt(D);
#if 1
      if(t1 > 10000.0 | t2 < 0.0) return false;

      double t = t1;
      if(t < 0.0) {
        t = t2;
        if(t > 10000.0) {
          return false;
        }
      }

#else

      if(D > 0.0 && t1 > 0.0) {
        // res.distance = t1;
        // res.hitPos = ray(t1);
        // res.hitNormal = normalize(res.hitPos - center);
        // res.hitSphere = this; // this is wrong because the type of res.hitspheres is "const" Sphere* 
        res = Hit(t1, ray(t1), normalize(ray(t1) - center), (Hitable*)this);
        return true;
      }

      return false;

#endif

      res = Hit(t1, ray(t1), normalize(ray(t1) - center), (Hitable*)this);
      return true;
    }
};
