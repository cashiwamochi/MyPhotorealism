#include <iostream>
#include <fstream>

#include "Vec3.hpp"
#include "Image.hpp"

using namespace std;

auto main(int argc, char* argv[]) -> int 
try
{
  const int height=512;
  const int width=512;
  Image img(height, width);
  for(int r = 0; r < height; ++r) {
    for(int c = 0; c < width; ++c) {
      img.setPixel(r, c,
                   Vec3(r/(double)img.height, c/(double)img.width, 255));
    }
  }

  img.writePPM("test_ppm.ppm");

  return 0;
}
catch(const char* e)
{
  std::cerr << e << std::endl;
  return 1;
}
