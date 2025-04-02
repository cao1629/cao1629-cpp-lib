#include <unordered_map>

struct LRUHandle {
  int key;
  int value;
  LRUHandle* next;
  LRUHandle* prev;
};


class LRUCache {
public:
  LRUCache() {
    dummy_head_ = new LRUHandle();
    dummy_head_->next = dummy_head_;
    dummy_head_->prev = dummy_head_;
  }

  void Insert(int key, int value) {

  }

  LRUHandle* Erase(int key) {

  }

private:
  std::unordered_map<int, LRUHandle*> hash_table_;
  LRUHandle* dummy_head_;
};