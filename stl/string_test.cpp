#include <gtest/gtest.h>
#include <string>

namespace cao1629 {

TEST(StringTest, TestSubstr) {
  std::string s = "0123456789";
  std::string sub = s.substr(0, 4);
  EXPECT_EQ(sub, "0123");
}


TEST(StringTest, TestConcat) {
  std::string s1 = "AAA";
  std::string s2 = "BBB";

  std::string s3 = s1 + s2;
  EXPECT_EQ(s3, "AAABBB");
}


TEST(StringTest, TestFind) {
  std::string s1 = "abcdefgabcdefg";
  int p = s1.find('c');
  EXPECT_EQ(p, 2);

  p = s1.find('c', 5);
  // search starting from idx 9
  EXPECT_EQ(p, 9);

  // search for a substr
  p = s1.find("def");
  EXPECT_EQ(p, 3);

  p = s1.rfind('c');
  EXPECT_EQ(p, 9);

}

}