#include <gtest/gtest.h>
#include <unordered_map>
#include <iostream>

namespace cao1629 {

TEST(MapTest, TestIterate) {
  std::unordered_map<int, int> m{{1,2}, {2,4}, {3,6}};
  // {1} c++ 11
  for (const auto &item : m) {
    std::cout << item.first << " -> " << item.second << std::endl;
  }

  // {2} c++ 17
  for (const auto &[k, v] : m) {
    std::cout << k << " -> " << v << std::endl;
  }
}


TEST(MapTest, TestRemove) {
  std::unordered_map<int, int> m{{1, 2}, {2, 4}, {3, 6}, {4, 8}, {5, 10}};
  // Manual loop
  for (auto it = m.begin(); it != m.end();)  {
    if (it->first % 2 == 0) {
      it = m.erase(it);
    } else {
      it++;
    }
  }
  std::unordered_map<int, int> expected{{1, 2}, {3, 6}, {5, 10}};
  EXPECT_EQ(m, expected);
}

}