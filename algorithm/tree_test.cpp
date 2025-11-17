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


// 105. Construct Binary Tree from Preorder and Inorder Traversal
class ConstructBinaryTreePreorderInorder {
public:

  TreeNode* dfs(std::vector<int>& preorder, std::vector<int>&inorder, int l1, int r1, int l2, int r2) {
    if (l1 > r1) {
      return nullptr;
    }

    // This is the root of the subtree we're constructing in this call.
    TreeNode* node = new TreeNode(preorder[l1]);
    if (l1 == r1) {
      return node;
    }

    // Divide inorder[l2 : r2] into two subtrees
    int p = l2;
    int len = 0;
    while (inorder[p] != preorder[l1]) {
      p++;
      len++;
    }

    // If the subtree is empty, len is 0, then l1+1 > l1+0. The next level dfs() will return nullptr.
    node->left_ = dfs(preorder, inorder, l1+1, l1+len, l2, p-1);
    node->right_ = dfs(preorder, inorder, l1+len+1, r1, p+1, r2);

    return node;
  }


};


}