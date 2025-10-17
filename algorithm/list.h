#pragma once
#include <vector>
#include <string>
#include <sstream>

namespace cao1629 {


struct ListNode {
  ListNode *next_;
  int val_;
  ListNode(): next_{nullptr}, val_{0} {}
  ListNode(int val): next_{nullptr}, val_{val} {}
};

ListNode *NewList(std::vector<int> &v) {
  ListNode *dummy_head = new ListNode();
  ListNode *p = dummy_head;
  for (auto e : v) {
    ListNode *node = new ListNode(e);
    p->next_ = node;
    p = p->next_;
  }
  return dummy_head->next_;
}

std::string ListToString(ListNode *head) {
  std::ostringstream oss;
  oss << "[";

  ListNode *p = head;
  while (p != nullptr) {
    oss << p->val_;
    if (p->next_ != nullptr) {
      oss << ", ";
    }
    p = p->next_;
  }

  oss << "]";
  return oss.str();
}

std::vector<int> ListToVector(ListNode *head) {
  std::vector<int> result;
  ListNode *p = head;
  while (p != nullptr) {
    result.push_back(p->val_);
    p = p->next_;
  }
  return result;
}


int numNodes(ListNode *head) {
  int num_nodes = 0;
  ListNode *p = head;
  while (p != nullptr) {
    num_nodes++;
    p = p->next_;
  }
  return num_nodes;
}

}