#include <gtest/gtest.h>
#include <vector>
#include <algorithm/tree.h>

namespace cao1629 {

TEST(TreeTest, TestPreorder) {
  std::vector<int> nums{5, 4, 8, 11, -1, 13, 4, 7, 2, -1, -1, -1, -1, -1, 1};
  TreeNode* tree = ConstructBinaryTree(nums);
  std::vector<int> result;
  Preorder(tree, result);
  std::vector<int> expected{5, 4, 11, 7, 2, 8, 13, 4, 1};
  EXPECT_EQ(result, expected);
}

TEST(TreeTest, TestInorder) {
  std::vector<int> nums{5, 4, 8, 11, -1, 13, 4, 7, 2, -1, -1, -1, -1, -1, 1};
  TreeNode* tree = ConstructBinaryTree(nums);
  std::vector<int> result = Inorder(tree);
  std::vector<int> expected{7, 11, 2, 4, 5, 13, 8, 4, 1};
  EXPECT_EQ(result, expected);
}

}