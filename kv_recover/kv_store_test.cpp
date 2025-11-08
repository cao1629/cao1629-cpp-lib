#include "kv_store.h"

#include <gtest/gtest.h>


namespace cao1629 {

TEST(RecoverKVTest, TestBasic) {
  KVStore kv_store("log1", "log2");
  kv_store.Put(1, 11);
  kv_store.Put(2, 22);
  kv_store.Put(3, 33);

  std::unordered_map<int, int> expected{{1, 11}, {2, 22} ,{3, 33}};
  EXPECT_EQ(kv_store.store_, expected);
}

TEST(RecoverKVTest, TestRecover) {
  {
    KVStore kv_store("log1.txt", "log2.txt");
    kv_store.Put(1, 11);
    kv_store.Put(2, 22);
    kv_store.Put(3, 33);
    kv_store.Remove(2);
  }

  {
    KVStore kv_store("log2.txt", "log3.txt");
    std::unordered_map<int, int> expected{{1, 11}, {3, 33}};
    EXPECT_EQ(kv_store.store_, expected);
  }

}



}