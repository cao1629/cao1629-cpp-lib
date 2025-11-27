#include <gtest/gtest.h>
#include <thread>
#include <atomic>

namespace cao1629 {

TEST(MemoryOrderTest, TestRelaxed) {
  bool ready = false;
  int value = 0;

  // concurrent code, undefined behaviour
  // instruction reordering might happen
  // e.g.
  // (1) ready = true
  // (2) value = 1
  std::thread t1([&ready, &value]() {
    value = 1;
    ready = true;
  });

  std::thread t2([&ready, &value]() {
    int v;
    if (ready) {
      // if instruction reordering happens in t1,
      // here even though we see ready is true, we might read value as 0.
      v = value;
    }
  });

  t1.join();
  t2.join();
}


// If acquire-load sees the value written by release-store, then
// there is a happen-before relationship between these load and store.
// then, every write in t1 before release-store will be seen by t2 after the acquire-load.
TEST(MemoryOrderTest, TestAcquireRelease) {
  std::atomic<bool> ready = false;
  int value = 0;

  std::thread t1([&ready, &value]() {
    value = 1;
    ready.store(true, std::memory_order_release);
  });

  std::thread t2([&ready, &value]() {
    int v;
    if (ready.load(std::memory_order_acquire)) {
      // if instruction reordering happens in t1,
      // here even though we see ready is true, we might read value as 0.
      v = value;
    }
  });

  t1.join();
  t2.join();
}

TEST(MemoryOrderTest, Test3) {
  int counter = 0;
  std::atomic<bool> atomic_counter;

  std::thread t1([&counter, &atomic_counter]() {

  });

  std::thread t2([&counter, &atomic_counter]() {

  });

  t1.join();
  t2.join();
  std::cout << counter << std::endl;
}
}
