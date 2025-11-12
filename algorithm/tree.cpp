#include <algorithm/tree.h>
#include <stack>

namespace cao1629 {


TreeNode* ConstructBinaryTree(std::vector<int>& nums) {

  int n = nums.size();
  std::vector<TreeNode*> tree;
  tree.push_back(nullptr);
  for (int i = 0; i < n; i++) {
    if (nums[i] == -1) {
      tree.push_back(nullptr);
    } else {
      TreeNode* node = new TreeNode(nums[i]);
      tree.push_back(node);
    }
  }

  for (int i = 1; i <= n; i++) {
    if (tree[i] == nullptr) {
      continue;
    }

    if (2*i <= n) {
      tree[i]->left_ = tree[2*i];
    }

    if (2*i+1 <= n) {
      tree[i]->right_ = tree[2*i+1];
    }
  }

  return tree[1];
}


void Preorder(TreeNode* node, std::vector<int> &result) {
  if (node == nullptr) {
    return;
  }

  result.push_back(node->val_);
  Preorder(node->left_, result);
  Preorder(node->right_, result);
}


std::vector<int> Inorder(TreeNode* root) {
  if (root == nullptr) {
    return {};
  }
  std::vector<int> result;
  std::stack<TreeNode*> stk;
  TreeNode* p = root;

  while (p!= nullptr || !stk.empty()) {
    while (p != nullptr) {
      stk.push(p);
      p = p->left_;
    }

    p = stk.top();
    stk.pop();
    result.push_back(p->val_);
    p = p->right_;
    }

  return result;
}

}