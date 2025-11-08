#include <gtest/gtest.h>



namespace cao1629 {

TEST(stdCopyMoveTest, TestCopy) {
  std::vector<int> v1{1, 2, 3, 4, 5};
  std::vector<int> v2(5);

  // v2's capacity must be greater than or equal to 5.
  // if its capacity is not enough, reverse().
  // std::copy will copy each element with each element's copy constructor or copy assignment.
  // If we want to use move constructor or move assignment of each element, use std::move instead.
  std::copy(v1.begin(), v1.end(), v2.begin());
  std::vector<int> expected{1, 2, 3, 4, 5};
  EXPECT_EQ(v2, expected);


  std::vector<int> v3{1, 2, 3, 4, 5};
  std::copy(v3.begin()+2, v3.end(), v3.begin());
  expected = {3, 4, 5, 4, 5};
  EXPECT_EQ(v3, expected);
}

}