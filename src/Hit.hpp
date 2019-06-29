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

};
