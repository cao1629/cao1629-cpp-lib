#include <algorithm/list.h>
#include <gtest/gtest.h>


namespace cao1629 {

TEST(ListTest, TestBasic) {
  std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  ListNode *node = NewList(v);
  std::string s = ListToString(node);
  std::cout << s << std::endl;
}

// 24. Swap Node in Pairs
ListNode *swapPairs(ListNode *node) {
  ListNode *dummy_head = new ListNode();
  dummy_head->next_ = node;
  ListNode *p = dummy_head;

  // At least two nodes left.
  while (p->next_ != nullptr && p->next_->next_ != nullptr) {
    ListNode *first = p->next_;
    ListNode *second = p->next_->next_;

    p->next_ = second;
    first->next_ = second->next_;
    second->next_ = first;

    p = p->next_->next_;
  }

  return dummy_head->next_;
}


ListNode *swapPairs2(ListNode *node) {
  auto *dummy_head = new ListNode();
  dummy_head->next_ = node;
  ListNode *prev = dummy_head;
  ListNode *p = node;

  while (p != nullptr && p->next_ != nullptr) {
    ListNode *first = p;
    ListNode *second = p->next_;
    prev->next_ = second;
    first->next_ = second->next_;
    second->next_ = first;

    p = first->next_;
    prev = first;
  }

  return dummy_head->next_;
}

ListNode *swapPairs3(ListNode *node) {
  if (node == nullptr || node->next_ == nullptr) {
    return node;
  }

  ListNode *first = node;
  ListNode *second = node->next_;
  first->next_ = swapPairs3(second->next_);
  second->next_ = first;
  return second;
}

TEST(ListTest, TestSwapPairs) {
  std::vector<int> v{1, 2, 3, 4};
  std::vector<int> expected{2, 1, 4, 3};
  EXPECT_EQ(ListToVector(swapPairs(NewList(v))), expected);
  EXPECT_EQ(ListToVector(swapPairs2(NewList(v))), expected);
  EXPECT_EQ(ListToVector(swapPairs3(NewList(v))), expected);
}

// 206. Reverse Linked List
ListNode *reverseList(ListNode *head) {
  ListNode *prev = nullptr;
  ListNode *p = head;

  while (p != nullptr) {
    ListNode *next = p->next_;
    p->next_= prev;
    prev = p;
    p = next;
  }

  return prev;
}

ListNode *reverse(ListNode *prev, ListNode *cur) {

  if (cur == nullptr) {
    return prev;
  }
  ListNode *t = cur->next_;
  cur->next_ = prev;
  return reverse(cur, t);
}

ListNode *reverseList2(ListNode *head) {
  return reverse(nullptr, head);
}

TEST(ListTest, TestReverseList) {
  std::vector<int> v{1, 2, 3, 4, 5};
  std::vector<int> expected{5, 4, 3, 2, 1};
  EXPECT_EQ(ListToVector(reverseList(NewList(v))), expected);
  EXPECT_EQ(ListToVector(reverseList2(NewList(v))), expected);
}


// 92. Reverse Linked List II: reverse a range in a linked list
ListNode *reverseBetween(ListNode *node, int left, int right) {
  ListNode *dummy_head = new ListNode();
  dummy_head->next_ = node;

  // go to list[left-1]
  ListNode *p = dummy_head;
  for (int i = 0; i < left; i++) {
    p = p->next_;
  }

  ListNode *prev = nullptr;
  ListNode *cur = p->next_;

  for (int i = left; i <= right; i++) {
    ListNode *t = cur->next_;
    cur->next_ = prev;
    prev = cur;
    cur = t;
  }

  p->next_->next_ = cur;
  p->next_ = prev;

  return dummy_head->next_;
}

TEST(ListTest, TestReverseBetween) {
  std::vector<int> v{1, 2, 3, 4, 5};
  std::vector<int> expected{1, 4, 3, 2, 5};
  EXPECT_EQ(ListToVector(reverseBetween(NewList(v), 1, 3)), expected);
}

// Reverse every k nodes in a linked list.
// 25. Reverse Nodes in k-Group
ListNode *reverseKGroup(ListNode *head, int k) {
  int remaining_nodes = numNodes(head);
  ListNode *dummy_head = new ListNode();
  dummy_head->next_ = head;


  ListNode *p = dummy_head;
  while (remaining_nodes >= k) {

    // Reverse the following k nodes.
    ListNode *prev = nullptr;
    ListNode *cur = p->next_;
    for (int i = 0; i < k; i++) {
      ListNode *next = cur->next_;
      cur->next_ = prev;
      prev = cur;
      cur = next;
    }

    ListNode *t = p->next_;
    p->next_->next_ = cur;
    p->next_ = prev;
    p = t;
    remaining_nodes -= k;
  }

  return dummy_head->next_;
}



TEST(ListTest, TestReverseKGroup) {
  std::vector<int> v1{1, 2, 3, 4, 5};
  std::vector<int> expected1{2, 1, 4, 3, 5};
  EXPECT_EQ(ListToVector(reverseKGroup(NewList(v1), 2)), expected1);

  std::vector<int> v2{1, 2, 3, 4, 5};
  std::vector<int> expected2{3, 2, 1, 4, 5};
  EXPECT_EQ(ListToVector(reverseKGroup(NewList(v2), 3)), expected2);
}

// 138 Copy Random List
class CopyRandomList {
public:
  struct Node {
    int val;
    Node *next;
    Node *random;
  };

  // nodes that have been copied are stored in node_map_
  std::unordered_map<Node*, Node*> node_map_;

  // Return a deep copy of the list that starts from "node"
  Node *copyRandomList(Node *node) {
    if (node == nullptr) {
      return nullptr;
    }

    if (node_map_.find(node) != node_map_.end()) {
      return node_map_[node];
    }

    Node *copy = new Node();
    // We first insert the copy into the map to avoid infinite recursion.
    node_map_[node] = copy;
    copy->val = node->val;
    copy->next = copyRandomList(node->next);
    copy->random = copyRandomList(node->random);
    return node_map_[node];
  }
};

// non-recursive version
// still need a map
// first round: build a new list with next pointers
// now all nodes have been copied and stored in the map.
// second round: set random pointers.
class CopyRandomList2 {

};


// 23. Merge K Lists
ListNode* MergeKLists(std::vector<ListNode*> lists) {
  ListNode* dummy_head = new ListNode(0);
  ListNode* p = dummy_head;

  struct Compare {
    bool operator()(const ListNode* lhs, const ListNode* rhs) {
      return lhs->val_ > rhs->val_;
    }
  };

  std::priority_queue<ListNode*, std::vector<ListNode*>, Compare> pq;

  for (auto *list : lists) {
    if (list != nullptr) {
      pq.push(list);
    }
  }

  while (!pq.empty()) {
    ListNode* t = pq.top();
    p->next_ = t;
    p = t;

    pq.pop();
    if (t->next_ != nullptr) {
      pq.push(t->next_);
    }
  }

  return dummy_head->next_;
}


TEST(ListTest, TestMergeKLists) {
  std::vector<int> v1{1, 4, 5};
  std::vector<int> v2{1, 3, 4};
  std::vector<int> v3{2, 6};
  ListNode* l1 = NewList(v1);
  ListNode* l2 = NewList(v2);
  ListNode *l3 = NewList(v3);

  std::vector<ListNode*> lists{l1, l2, l3};
  ListNode* merged = MergeKLists(lists);
  auto result = ListToVector(merged);
  std::vector<int> expected{1, 1, 2, 3, 4, 4, 5, 6};
  EXPECT_EQ(result, expected);
}

// 141. Linked List Cycle
bool ListHasCycle(ListNode* head) {
  ListNode* slow = head;
  ListNode* fast = head;

  while (fast != nullptr && fast->next_ != nullptr) {
    fast = fast->next_->next_;
    slow = slow->next_;

    if (fast == slow) {
      return true;
    }
  }

  return false;
}


};