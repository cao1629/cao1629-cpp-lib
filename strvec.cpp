#include <iostream>
#include <string>
#include <memory>


class StrVec {
public:
  StrVec() : elements_(nullptr), first_free_(nullptr), cap_(nullptr) { }

  // Copy constructor
  StrVec(const StrVec&) {

  }

  // Move constructor
  // noexcept: the function will not throw any exceptions
  StrVec(StrVec &&s) noexcept : elements_(s.elements_), first_free_(s.first_free_), cap_(s.cap_) {
    s.elements_ = s.first_free_ = s.cap_ = nullptr;
  }

  // Move assignment operator
  StrVec &operator=(StrVec &&rhs) noexcept {
    // Check for self-assignment
    if (this != &rhs) {
      Free();
      elements_ = rhs.elements_;
      first_free_ = rhs.first_free_;
      cap_ = rhs.cap_;
      rhs.elements_ = rhs.first_free_ = rhs.cap_ = nullptr;
    }
    return *this;
  }

  StrVec &operator=(const StrVec&);

  ~StrVec() { Free(); }

  void PushBack(const std::string&);

  size_t Size() const { return first_free_ - elements_; }

  size_t Capacity() const { return cap_ - elements_; }

  std::string *begin() const { return elements_; }

  std::string *end() const { return first_free_; }


private:

  // Pointer to the first element in the array
  std::string *elements_;

  // Pointer to one past the last element in the array
  std::string *first_free_;

  // Pointer to one past the allocated memory
  std::string *cap_;

  static std::allocator<std::string> alloc_;

  void Resize() {
    // When the size of the array is 0, allocate memory for one element
    // When the size of the array is not 0, allocate memory for twice the size of the array
    int newcap = Size() ? 2 * Size() : 1;

    // Allocate new memory
    auto newdata = alloc_.allocate(newcap);

    // Move the data from the old memory to the new memory
    auto dest = newdata;
    auto old = elements_;
    

    for (size_t i = 0; i != Size(); ++i) {
      // Call the move constructor of std::string
      alloc_.construct(dest++, std::move(*old++));
    }

    Free();

    elements_ = newdata;
    first_free_ = dest;
    cap_ = elements_ + newcap;
  }


  void Free() {
    // If the pointer is not nullptr, free the memory
    if (elements_) {
      // Call the destructor of each element in the array
      for (auto p = first_free_; p != elements_; ) {
        alloc_.destroy(--p);
      }
      // Release the memory
      alloc_.deallocate(elements_, cap_ - elements_);
    }
  }


  // void chk_n_alloc() { if (Size() == capacity()) reallocate(); }
  std::pair<std::string*, std::string*> alloc_n_copy(const std::string*, const std::string*);
};