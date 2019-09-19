#pragma once

#include "Vec3.hpp"
#include "Ray.hpp"

class Sky {
  public:
    Sky() {};
    virtual Vec3 getRadiance(const Ray& ray) const = 0;
};

class UniformSky : public Sky {
  public:
    Vec3 color;
    UniformSky(const Vec3& _color) : color(_color) {};

    Vec3 getRadiance(const Ray& ray) const {
      return color;
    }
};

class SimpleSky : public Sky {
  public:
    SimpleSky() {};

    Vec3 getRadiance(const Ray& ray) const {
      double t = (ray.direction.y + 1.0) / 2.0;
      return (1.0 - t)*Vec3(1.0) + t*Vec3(0.7,0.8,1.0);
    }
};
