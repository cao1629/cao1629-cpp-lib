#include <gtest/gtest.h>
#include <unordered_map>
#include <iostream>

namespace cao1629 {

TEST(MapTest, TestIterateMap) {
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

}