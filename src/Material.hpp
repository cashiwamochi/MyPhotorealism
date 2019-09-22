#pragma once
#include "random.hpp"

double absCosTheta(const Vec3& v) {
  return std::abs(v.y);
}

bool refract(const Vec3& v, Vec3& r, const Vec3& n, double n1, double n2) {
  double cos = absCosTheta(v);
  double sin = std::sqrt(std::max(1.0 - cos*cos, 0.0));
  double alpha = n1/n2 * sin;

  if(alpha*alpha > 1.0) {
    return false;
  }

  r = n1/n2 * (-v + dot(v, n)*n) - std::sqrt(1.0 - alpha*alpha)*n;

  return false;
}

Vec3 reflect(const Vec3& v, const Vec3& n) {
  return -v + 2.0*dot(v,n)*n;
}

double cosTheta(const Vec3& v) {
  return v.y;
}

class Material {
  public:
    virtual Vec3 sample(const Vec3& wo, Vec3& wi, double& pdf) const = 0;
};

class Diffuse : public Material {
  public:
    Vec3 rho;
    
    Diffuse(const Vec3& _rho) : rho(_rho) {};

    Vec3 sample(const Vec3& wo, Vec3& wi, double& pdf) const {
      double u = rnd();
      double v = rnd();
      double theta = 0.5 * std::acos(1.0 - 2.0*u);
      double phi = 2*M_PI * v;

      double x = std::cos(phi)*std::sin(theta);
      double y = std::cos(theta);
      double z = std::sin(phi)*std::sin(theta);

      wi = Vec3(x, y, z);

      pdf = std::cos(theta)/M_PI;

      return rho/M_PI;
    }
};

double fresnel(const Vec3& v, const Vec3& n, double n1, double n2) {
  double f0 = std::pow((n1-n2)/(n1+n2), 2.0);
  double cos = absCosTheta(v);
  return f0 + (1.0 - f0)*std::pow(1.0 - cos, 5.0);
}

class Mirror : public Material {
  public:
    Mirror() {};

    Vec3 sample(const Vec3& wo, Vec3& wi, double& pdf) const {
      wi = reflect(wo, Vec3(0.0,1.0,0.0));

      pdf = 1.0;

      return 1.0/cosTheta(wi) * Vec3(1.0);
    }
};
