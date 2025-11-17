#include <gtest/gtest.h>



namespace cao1629 {

TEST(SerDesTest, TestEncodeVector) {
  std::vector<int> nums{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::vector<uint8_t> encoded;

  // Each number in the vector takes 4 bytes.
  encoded.reserve(4*nums.size());

  for (auto &num : nums) {
    auto *p = reinterpret_cast<uint8_t*>(&num);
    encoded.insert(encoded.end(), p, p+4);
  }

  auto* data = encoded.data();
  std::vector<int> decoded;

  auto *p = data;
  for (int i = 0; i < nums.size(); i++) {
    auto *ip = reinterpret_cast<int*>(p);
    decoded.insert(decoded.end(), ip, ip+1);
    p = p+4;
  }

  EXPECT_EQ(nums, decoded);
}

}