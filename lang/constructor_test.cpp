#include <gtest/gtest.h>
#include <vector>
#include <iostream>
#include <classes/point.h>

namespace cao1629 {

class Line {

public:

private:
  Point p1_;
  Point p2_;
};


TEST(ConstructorTest, Test1) {
  std::vector<Point> points;
  Point p{1,2};
  std::cout <<  "---" << std::endl;
  points.push_back(p);
}

}
