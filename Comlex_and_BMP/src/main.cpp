#include <iostream>

#include "math/complex.h"
#include "bmp/bmp.h"

int main() {
  //Complex a;
  //std::cout << Complex(-10, -20);
  //std::cin >> a;
  //std::cout << a;
  bmp BMP(1920, 1080);  

  BMP.setPixel(0, 0, {255, 0, 0});
  BMP.setPixel(0, 1, {0, 255, 0});
  BMP.setPixel(1, 0, {0, 0, 255});

  //BMP.DrawArbLine(5, 1, 9, 1, {255, 255,0});
  //BMP.DrawArbLine(1, 2, 1, 7, {255, 255,0});
  //BMP.DrawArbLine(1, 1, 5, 8, {255, 255,0});

  BMP.save("test.bmp");
  BMP.DrawComplex(-2, -1, -1, 1, 100);  
  BMP.save("Complex.bmp");

  return 0;
}