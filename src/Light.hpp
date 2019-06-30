#pragma once

#include "Vec3.hpp"

class Light {
  public:
    Vec3 color;

    Light(const Vec3& _color) : color(_color) {};

    Vec3 Le() const {
      return color;
    }
};
