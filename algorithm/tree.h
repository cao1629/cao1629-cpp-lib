#pragma once
#include <vector>

namespace cao1629 {

struct TreeNode {
  int val_;
  TreeNode* left_;
  TreeNode* right_;

  TreeNode(int val): val_(val) {}
};

// construct a binary tree from a vector.
// -1 means this position is empty.
TreeNode* ConstructBinaryTree(std::vector<int> &nums);

void Preorder(TreeNode* node, std::vector<int> &result);

std::vector<int> Inorder(TreeNode* root);

}