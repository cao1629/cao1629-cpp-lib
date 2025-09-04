#include <gtest/gtest.h>
#include <unordered_map>
#include "o/point.h"

namespace cao1629 {

TEST(MemoryBasicTest, SimpleTest) {
  char mem[8];
  auto p = reinterpret_cast<int*>(mem);
  *p = 10;
  *(p+1) = 20;

  int &v = p[0];
  std::move(p+1, p+2, p);
  EXPECT_EQ(v, 20);
}


TEST(MemoryBasicTest, RefCopyTest) {
  Point p1{1,2};
  Point p2{3,4};
  Point &r1 = p1;
  Point &r2 = p2;
  std::pair<Point, Point> pr{r1, r2};
}


TEST(MemoryBasicTest, Test1) {
  std::vector<Point> points{{1,2}, {3,4}, {5,6}};
  std::vector<Point> some_other_points();
}

}