#pragma once

#include "Vec3.hpp"

class Sphere;

class Hit{
  public:
    double distance;
    Vec3 hitPos;
    Vec3 hitNormal;
    const Sphere* hitSphere;

    Hit() {
      distance = 1000000.0;
    };

    Hit(const double& _d, const Vec3& _hitPos, const Vec3& _hitNormal, const Sphere* _hitSphere)
    : distance(_d), hitPos(_hitPos), hitNormal(_hitNormal), hitSphere(_hitSphere) 
    {}

};
