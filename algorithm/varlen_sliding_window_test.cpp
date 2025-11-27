#include <gtest/gtest.h>
#include <string>

namespace cao1629 {

// 3. Longest Substring Without Repeating Characters
int lengthOfLongestSubstrNoRepeatingCharacter(std::string s) {
  int result = 0;
  std::unordered_map<char, int> map;
  int p1 = 0;
  int p2 = 0;
  for (; p2 < s.size(); p2++) {
    map[s[p2]]++;
    while (map[s[p2]] > 1) {
      p1++;
      map[s[p1]]--;
    }
    result = std::max(result, p2-p1+1);
  }
  return result;
}

TEST(VarLenSlidingWindowTest, TestNoRepeatingCharacterSubstr) {
  std::string s = "abcabcbb";
  int ans = 3;
  EXPECT_EQ(lengthOfLongestSubstrNoRepeatingCharacter(s), ans);
}


// 2831. Find the Longest Equal Subarray
int

}