#pragma once

#include <cmath>
#include "Vec3.hpp"
#include "Ray.hpp"
#include "Hit.hpp"

class Sphere {
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
      double t1 = -b - std::sqrt(D);
      double t2 = -b + std::sqrt(D);

      if(D > 0.0 && t1 > 0.0) {
        // res.distance = t1;
        // res.hitPos = ray(t1);
        // res.hitNormal = normalize(res.hitPos - center);
        // res.hitSphere = this;
        res = Hit(t1, ray(t1), normalize(res.hitPos - center), this);
        return true;
      }

      return false;
    }
};
