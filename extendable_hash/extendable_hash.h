#pragma once
#include <vector>
#include <list>
#include <memory>

namespace cao1629 {


class Bucket {
public:
  Bucket(int capacity): capacity_(capacity), depth_(0) {}


  // Before adding an entries, see if this bucket is full.
  // If true, do redistribution.
  void Add(int k, int v);

  bool Lookup(int k, int& v);

  bool Remove(int k);

  bool IsFull() {
    if (list_.size() == capacity_) {
      return true;
    }
    return false;
  }



  std::list<std::pair<int, int>> list_;
  int capacity_;
  int depth_;
};

class ExtendableHashMap {
public:
  void Add(int k, int v);

  bool Lookup(int k, int& v);

  bool Remove(int k);

  int IndexOf(int k);

  ExtendableHashMap(int bucket_capacity): bucket_capacity_(bucket_capacity), global_depth_(0) {}

  void EnsureRoom(std::shared_ptr<Bucket> target_bucket);

private:
  int global_depth_;
  std::vector<std::shared_ptr<Bucket>> buckets_;
  int bucket_capacity_;
};



}
