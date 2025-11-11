#include <gtest/gtest.h>
#include <vector>
#include <iostream>

namespace cao1629 {


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

// Given the value of an element, remove it from the vector
TEST(VectorTest, TestRemoveElement) {
  std::vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  // -1 Remove an element with a specific value
  // (1) find its iterator
  // (2) erase
  auto it = std::find(v.begin(), v.end(), 8);
  v.erase(it);
  std::vector<int> expected1{1, 2, 3, 4, 5, 6, 7, 9, 10};
  EXPECT_EQ(v, expected1);

  // -2 Remove a range
  auto it1 = v.begin() + 5;
  auto it2 = v.end();
  v.erase(it1, it2);
  std::vector<int> expected2{1, 2, 3, 4, 5};
  EXPECT_EQ(v, expected2);
}

TEST(vectorTest, TestSort) {
  // Sort a vector in a reversed order
  std::vector<int> v{1, 2, 3, 4, 5};
  std::sort(v.begin(), v.end(), std::greater<int>());
  std::vector<int> expected{5, 4, 3, 2, 1};
  EXPECT_EQ(v, expected);

  // Sort elements with a custom comparator
  std::vector<int> v2{-5, -3, -1, 2, 4};
  std::sort(v2.begin(), v2.end(), [](int lhs, int rhs) {
    return lhs*lhs < rhs*rhs;
  });
  std::vector<int> expected2{-1, 2, -3, 4, -5};

}


TEST(vectorTest, TestRemove) {
  // -1 Remove all 0
  std::vector<int> v{1, 0, 2, 0, 3, 0, 4, 0, 5, 0};

  // std::remove moves the elements we want to remove to the end of the vector
  auto it = std::remove(v.begin(), v.end(), 0);
  v.erase(it, v.end());
  std::vector<int> expected{1, 2, 3, 4, 5};
  EXPECT_EQ(v, expected);


  // -2 Remove all even numbers
  std::vector<int> v2{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  auto it2 = std::remove_if(v2.begin(), v2.end(), [](int val) {
    return val%2 == 0;
  });
  v2.erase(it2, v2.end());
  std::vector<int> expected2{1, 3, 5, 7, 9};
  EXPECT_EQ(v2, expected2);
}


}