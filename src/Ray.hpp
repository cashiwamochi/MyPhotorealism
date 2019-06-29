#pragma once

#include <iostream>
#include "Vec3.hpp"

class Ray {
  public:
    Vec3 origin;
    Vec3 direction;

    Ray(const Vec3& _origin, const Vec3& _direction)
      : origin(_origin), direction(_direction)
    {

    }

    Vec3 operator()(double t) const {
      return origin + t*direction;
    }
};
