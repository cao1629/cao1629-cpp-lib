#include <gtest/gtest.h>
#include <vector>
#include <iostream>

namespace cao1629 {

TEST(VectorTest, Test1) {
  std::vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  v.erase(std::find(v.begin(), v.end(), 5));
  for (auto e : v) {
    std::cout << e << std::endl;
  }
}

TEST(VectorTest, Test2) {
  std::vector<int> v{1,2};
  std::cout << v[2] << std::endl;
}



TEST(VectorTest, Test3) {
  std::vector<int> v{1,2,3,4,5,6,7};
  std::reverse(v.begin(), v.end());
  std::vector<int> expected{7,6,5,4,3,2,1};
  EXPECT_EQ(v, expected);
}


}