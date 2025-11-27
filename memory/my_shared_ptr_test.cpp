#include <atomic>


namespace cao1629 {
template <typename T>
class SharedPtr {
public:
  SharedPtr() : p_(nullptr) {
  }

  explicit SharedPtr(T* p) : p_(p) {
    if (!p) {
      ref_ = nullptr;
    }
    else {
      ref_ = new std::atomic<std::size_t>(1);
    }
  }

  // other might be a null pointer
  SharedPtr(const SharedPtr& other) {
    p_ = other.p_;
    ref_ = other.ref_;
    if (ref_) {
      ref_->fetch_add(1);
    }
  }

  SharedPtr& operator=(const SharedPtr& other) {
    if (this != &other) {
      Release();
      p_ = other.p_;
      ref_ = other.ref_;
      // other might be a null shared pointer
      if (ref_) {
        ref_->fetch_add(1);
      }
    }
    return *this;
  }


  SharedPtr(SharedPtr&& other) noexcept {
    Release();
    p_ = other.p_;
    ref_ = other.ref_;
    other.p_ = nullptr;
    other.ref_ = nullptr;
  }

  SharedPtr& operator=(SharedPtr&& other) noexcept {
    if (*this != other) {
      Release();
      p_ = other.p_;
      ref_ = other.ref_;
      other.p_ = nullptr;
      other.ref_ = nullptr;
    }
    return *this;
  }

  T* operator->() const {
    return p_;
  }

  void Reset(T* p = nullptr) {
    Release();
    p_ = p;
    if (p_) {
      ref_ = new std::atomic<std::size_t>(1);
    }
  }


  ~SharedPtr() {
    Release();
  }

  T* p_;
  std::atomic<std::size_t>* ref_;

  void Release() {
    if (ref_ && ref_->fetch_sub(1) == 1) {
      delete p_;
      delete ref_;
      p_ = nullptr;
      ref_ = nullptr;
    }
  }
};
}
