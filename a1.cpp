#include <algorithm>
#include <cassert>
#include <complex>
#include <iostream>
#include <vector>
#include "DataClass/point.h"
#include <cstring>




int main() {
  Point points[4] = {
      {1, 2},
      {3, 4},
      {5, 6},
      {7, 8}
  };

  memmove(points + 1, points, 2 * sizeof(Point)); // Copy first two points to the last two positions

//  std::copy(points, points+2, points+2);

  for (const auto &point : points) {
    std::cout << point.ToString() << std::endl;
  }
}