#pragma once
#include <random>

double rnd() {
  static std::random_device rnd_dev;
  static std::mt19937 mt(rnd_dev());
  static std::uniform_real_distribution<> dist(0,1);

  return dist(mt);
}
