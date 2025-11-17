#include "extendable_hash.h"


namespace cao1629 {

void Bucket::Add(int k, int v) {
  auto p = std::find_if(list_.begin(), list_.end(), [k](auto& e) {
    return e.first == k;
  });

  if (p != list_.end()) {
    p->second = v;
  }
  else {
    list_.emplace_back(k, v);
  }
}

bool Bucket::Lookup(int k, int& v) {
  auto p = std::find_if(list_.begin(), list_.end(), [k](auto& e) {
    return e.first == k;
  });

  if (p != list_.end()) {
    v = p->second;
    return true;
  }

  return false;
}


bool Bucket::Remove(int k) {
  auto p = std::find_if(list_.begin(), list_.end(), [k](auto& e) {
    return e.first == k;
  });

  if (p != list_.end()) {
    list_.erase(p);
    return true;
  }

  return false;
}


void ExtendableHashMap::Add(int k, int v) {
  EnsureRoom(buckets_[IndexOf(k)]);
  auto target_bucket = buckets_[IndexOf(k)];
  target_bucket->Add(k, v);
}


void ExtendableHashMap::EnsureRoom(std::shared_ptr<Bucket> target_bucket) {
  while (target_bucket->IsFull()) {

    // increase bucket's depth
    if (target_bucket->depth_ < global_depth_) {

      // Redistribute the current bucket into two buckets
      int old_bucket_depth = target_bucket->depth_;
      auto bucket0 = std::make_shared<Bucket>(bucket_capacity_);
      bucket0->depth_ = old_bucket_depth+1;
      auto bucket1 = std::make_shared<Bucket>(bucket_capacity_);
      bucket0->depth_ = old_bucket_depth+1;

      auto mask = 1 << old_bucket_depth;
      for (const auto& entry : target_bucket->list_) {
        auto hashcode = std::hash<int>()(entry.first);
        if ((hashcode&mask) == 0) {
          bucket0->Add(entry.first, entry.second);
        } else {
          bucket1->Add(entry.first, entry.second);
        }
      }

      // bucket: 0
      // dirs: 000, 010, 100, 110
      // 00 -> 000, 100
      // 10 -> 010, 110

      for (int i = 0; i < buckets_.size(); i++) {
        if (buckets_[i] == target_bucket) {
          if ((i&mask) == 0) {
            buckets_[i] = bucket0;
          } else {
            buckets_[i] = bucket1;
          }
        }
      }

      continue;
    }

    // Increase global depth
    int old_num_buckets = buckets_.size();
    buckets_.resize(old_num_buckets << 1);
    for (int i = 0; i < old_num_buckets; i++) {
      buckets_[i+old_num_buckets] = buckets_[i];
    }
    global_depth_++;
  }
}


bool ExtendableHashMap::Lookup(int k, int& v) {
  auto target_bucket = buckets_[IndexOf(k)];
  return target_bucket->Lookup(k, v);
}


bool ExtendableHashMap::Remove(int k) {
  auto target_bucket = buckets_[IndexOf(k)];
  return target_bucket->Remove(k);
}


int ExtendableHashMap::IndexOf(int k) {
  return std::hash<int>()(k) & ((1 << global_depth_) - 1);
}

}
