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


TEST(ConstructorTest, Test2) {
  std::vector<int> v{1,2,3,4};
  for (auto it = v.begin(); it != v.end(); ) {
    if (*it % 2 == 0)
      v.erase(it);   // 使用 erase 的返回值继续遍历（正确）
    else
      ++it;               // 不删除时正常前进
  }
  int a = 1;
}

}
