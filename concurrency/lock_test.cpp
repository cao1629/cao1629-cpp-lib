#include <gtest/gtest.h>
#include <mutex>
#include <iostream>
#include <thread>
#include <condition_variable>

namespace cao1629 {
struct BankAccount {
  explicit BankAccount(int balance) : balance_{balance} {
  }

  int balance_;
  std::mutex m;
  std::condition_variable cv;
};

// Why not we have one mutex inside each transfer() call.
// In this case, transfer(A->B) and transfer(C->D) cannot happen simultaneously
void transfer(BankAccount& from, BankAccount& to, int amount) {
  // don't actually take the locks yet
  std::unique_lock lock1{from.m, std::defer_lock};
  std::unique_lock lock2{to.m, std::defer_lock};

  // lock both unique_locks without deadlock
  // how does it avoid deadlock?
  // attempt to lock both mutexes atomically
  //
  // in which situation where deadlock happens?
  // transfer(A->B) and transfer(B->A) runs simultaneously
  std::lock(lock1, lock2);

  from.balance_ -= amount;
  to.balance_ += amount;
}


void transfer2(BankAccount& from, BankAccount& to, int amount) {
  std::lock(from.m, to.m);

  std::unique_lock<std::mutex> lock1(from.m, std::adopt_lock);
  std::unique_lock<std::mutex> lock2(to.m, std::adopt_lock);

  from.balance_ -= amount;
  to.balance_ += amount;
}


// Use scoped_lock
void transfer3(BankAccount& from, BankAccount& to, int amount) {
  std::scoped_lock lock(from.m, to.m);
  from.balance_ -= amount;
  to.balance_ += amount;
}


// Wait when balance is insufficient
void transfer4(BankAccount& from, BankAccount& to, int amount) {
  std::unique_lock lock1{from.m, std::defer_lock};
  std::unique_lock lock2{to.m, std::defer_lock};

  // Lock both mutexes without deadlock
  std::lock(lock1, lock2);

  // Wait until from account has sufficient balance
  while (from.balance_ < amount) {
    from.cv.wait(lock1);
  }

  from.balance_ -= amount;
  to.balance_ += amount;

  // Notify waiting threads that balance has changed
  // Why notify all? At this moment we do not know which waiting thread will satisfy the condition.
  to.cv.notify_all();
}


TEST(LockTest, TestUniqueLockDeferLock) {
  BankAccount acc1{100};
  BankAccount acc2{50};

  // By default, copy is passed into a thread.
  // Use std::ref() to pass reference instead.
  std::thread t1{transfer, std::ref(acc1), std::ref(acc2), 10};
  std::thread t2{transfer, std::ref(acc2), std::ref(acc1), 5};

  t1.join();
  t2.join();

  std::cout << "acc1: " << acc1.balance_ << "\n"
    "acc2: " << acc2.balance_ << '\n';
}


TEST(LockTest, TestUniqueLockAdoptLock) {
  std::mutex mu;
  mu.lock();

  // This thread will deadlock itself because this lock is not a reentrant lock.
  // c++ provides reentrant lock: std::recursive_mutex
  // std::unique_lock<std::mutex> lock(mu);

  // only manage unlocking
  std::unique_lock<std::mutex> lock(mu, std::adopt_lock);

}
}
