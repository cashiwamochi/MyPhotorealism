#pragma once

#include <cmath>
#include "Vec3.hpp"
#include "Ray.hpp"
#include "Hit.hpp"

class Sphare {
  public:
    Vec3 center;
    double radius;
    
    Sphere(const Vec3& _center, const double& _radius) {
      center = _center;
      radius = _radius;
    }

    bool intersect(const Ray& ray, Hit& res) const {
      double b = dot(ray.direction, ray.origin-center);
      double c = (ray.origin - center).length2() - radius*radius;

      double D = b*b - c;
      double t1 = -b - std::sqrt(D);
      double t2 = -b + std::sqrt(D);
    }
};
