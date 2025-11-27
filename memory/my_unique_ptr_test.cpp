


#include "classes/point.h"

namespace cao1629 {

template <typename T>
class UniquePtr {

public:
  UniquePtr(T* p): p_(p) {}

  UniquePtr(const UniquePtr& other) = delete;

  UniquePtr& operator=(const UniquePtr& other) = delete;

  UniquePtr(UniquePtr&& other) noexcept : p_(other.p_){
      other.p_ = nullptr;
  }

  UniquePtr& operator=(UniquePtr&& other) noexcept {
    if (*this != other) {
      p_ = other.p_;
      other.p_ = nullptr;
    }
    return *this;
  }

  void Reset(T* p = nullptr) {
    delete p_;
    p_ = p;
  }

  T* Release() {
    T* t = p_;
    p_ = nullptr;
    return t;
  }

  ~UniquePtr() {
    delete p_;
  }

private:
  T* p_;
};





}
