#pragma once 

#include <random>

template <typename T>
T clamp(T x, T xmin, T xmax) {
  if(x < xmin) return xmin;
  else if(x > xmax) return xmax;
  else return x;
}

double rnd() {
  static std::random_device rnd_dev;
  static std::mt19937 mt(rnd_dev());
  static std::uniform_real_distribution<> dist(0,1);

  return dist(mt);
}
