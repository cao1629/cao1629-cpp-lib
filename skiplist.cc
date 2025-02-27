#include "skiplist.h"
#include <stack>
#include <cmath>

using namespace std;

bool SkipList::Find(int num) {
  Node *p = head_;
  while (p != nullptr) {
    while (p->next_ != nullptr && p->next_->val_ < num) {
      p = p->next_;
    }
    if(p->next_ != nullptr && p->next_->val_ == num) {
      return true;
    }
    p = p->down_;
  }
  return false;
}

void SkipList::Add(int num) {
  Node *p = head_;
  stack<Node*> nodes;
  while (p != nullptr) {
    while (p->next_ != nullptr && p->next_->val_ < num) {
      p = p->next_;
    }
    // [1] p->next_->val_ ≥ num
    // [2] p->next_ == nullptr  --> add node to the end
    nodes.push(p);
  }

  float rd = 0;
  Node *prev = nullptr;
  while (!nodes.empty() && rd < 0.5) {
    Node *p = nodes.top();
    nodes.pop();
    Node *newnode = new Node(num, p->next_, prev);
    Node *prev = newnode;
    p->next_ = newnode;
    rd = ((double) rand() / (RAND_MAX)) + 1;
  }

  if (rd < 0.5) {
    head_ = new Node(INT_MIN, nullptr, head_);
  }
}

bool SkipList::Remove(int num) {
  Node *p = head_;
  bool found = false;
  while (p != nullptr) {
    while (p->next_ != nullptr && p->next_->val_ < num) {
      p = p->next_;
    }
    if (p->next_ != nullptr && p->next_->val_ == num) {
      Node *t = p->next_;
      p->next_ = t->next_;
      delete p;
      found = true;
    }
    p = p->down_;
  }
  return found;
}