#pragma once 

template <typename T>
T clamp(T x, T xmin, T xmax) {
  if(x < xmin) return xmin;
  else if(x > xmax) return xmax;
  else return x;
}
