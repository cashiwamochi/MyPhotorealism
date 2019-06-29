#pragma once
#include "Vec3.hpp"
#include "Ray.hpp"

class Camera {
  public:
    Vec3 camPos;
    Vec3 camForward;
    Vec3 camRight;
    Vec3 camUp;

    Camera(const Vec3& _camPos, const Vec3& _camForward)
    {
      camPos = _camPos;
      camForward = _camForward;
      orthonormalBasis(camForward, camRight, camUp);

      std::cout << "CamPos = " << camPos << std::endl;     
      std::cout << "CamForward = " << camForward << std::endl;     
      std::cout << "CamRight = " << camRight << std::endl;     
      std::cout << "CamUP = " << camUp << std::endl;     
    }

    virtual Ray getRay(double u, double v) const = 0;
};

class PinholeCamera : public Camera {
  public:
    double pinholeDist;

    PinholeCamera(const Vec3& _camPos, const Vec3& _camForward, double _pinholeDist)
    : Camera(_camPos, _camForward), pinholeDist(_pinholeDist)
    {
      // 
    }

    Ray getRay(const double u, const double v) const {
      Vec3 pihholePos = camPos + pinholeDist*camForward;
      Vec3 sensorPos = camPos + u*camRight + v*camUp;
      return Ray(sensorPos, normalize(pihholePos - sensorPos));
    }
};
