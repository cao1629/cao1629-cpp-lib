#include <gtest/gtest.h>
#include <string>

namespace cao1629 {

TEST(StringTest, TestSubstr) {
  std::string s = "0123456789";
  std::string sub = s.substr(0, 4);
  EXPECT_EQ(sub, "0123");
}

}