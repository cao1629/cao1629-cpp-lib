#include <mutex>

namespace cao1629 {


class Singleton {
public:
  static Singleton* GetInstance() {
    std::unique_lock<std::mutex> lock;
    if (instance_ == nullptr) {
      instance_ = new Singleton();
    }
    return instance_;
  }

  static Singleton* instance_;
  static std::mutex mu;

private:

  Singleton() {}

  Singleton(const Singleton& other) {}
};

}