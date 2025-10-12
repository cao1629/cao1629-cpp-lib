#include <gtest/gtest.h>
#include <classes/point.h>

namespace cao1629 {

TEST(UniquePtrTest, Test1) {
  std::unique_ptr<Point> p{new Point{1,2}};
}

}