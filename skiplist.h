#include <climits>


class SkipList {
public:

  SkipList() {
    head_ = new Node();
  }

  void Add(int num);

  bool Remove(int num);

  bool Find(int num);

private:
  struct Node {
    int val_;
    Node *next_;
    Node *down_;

    Node(): val_(INT_MIN), next_(nullptr), down_(nullptr) {}
    Node(int val, Node *next, Node *down): val_(val), next_(next), down_(down) {}
  };

  Node *head_;
};