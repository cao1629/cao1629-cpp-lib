#include <mutex>
#include <condition_variable>

namespace cao1629 {

class RWLock {
public:

  void RLock() {
    std::unique_lock<std::mutex> lock(mu_);

    while (is_writing_) {
      can_read_.wait(lock);
    }

    readers_++;
  }

  void RUnlock() {
    std::unique_lock<std::mutex> lock;
    readers_--;
    if (readers_ == 0) {
      can_write_.notify_one();
    }
  }

  void WLock() {
    std::unique_lock<std::mutex> lock;
    while (is_writing_ || readers_ > 0) {
      can_write_.wait(lock);
    }
    is_writing_ = true;
  }

  void WUnlock() {
    std::unique_lock<std::mutex> lock;
    is_writing_ = false;
    can_read_.notify_one();
    can_write_.notify_one();
  }

  int readers_;
  std::mutex mu_;
  std::condition_variable can_read_;
  std::condition_variable can_write_;
  bool is_writing_;
};
}
