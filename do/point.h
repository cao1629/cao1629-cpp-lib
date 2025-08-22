#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>
#include <optional>
#include <tuple>
#include <list>


class Point {
public:
  // Default Constructor
  Point() {
    std::cout << "Default Constructor called" << std::endl;
  }

  // Constructor
  Point(int x, int y) : x_(x), y_(y) {
    std::cout << "Constructor called: " + ToString() << std::endl;
  }

  // Copy constructor
  Point(const Point &p) : x_(p.x_), y_(p.y_) {
    std::cout << "Copy constructor called" << std::endl;
  }

  // Move constructor
  Point(Point &&p) noexcept : x_(p.x_), y_(p.y_) {
    std::cout << "Move constructor called" << std::endl;
    p.x_ = 0;
    p.y_ = 0;
  }

  // Move assignment operator
  Point& operator=(Point &&p) noexcept {
    std::cout << "Move assignment operator called" << std::endl;
    if (this != &p) {
      x_ = p.x_;
      y_ = p.y_;
      p.x_ = 0;
      p.y_ = 0;
    }
    return *this;
  }

  // Destructor
  ~Point() {
    std::cout << "Destructor called: " + ToString() << std::endl;
  }

  std::string ToString() const {
    return "(" + std::to_string(x_) + ", " + std::to_string(y_) + ")";
  }

  // Assignment operator
  Point& operator=(const Point &p) {
    std::cout << "Assignment operator called" << std::endl;
    if (this != &p) {
      x_ = p.x_;
      y_ = p.y_;
    }
    return *this;
  }

  bool operator<(const Point &other) const {
    return x_*x_ + y_*y_ < other.x_*other.x_ + other.y_*other.y_;
  }

  int x() const { return x_; }
  int y() const { return y_; }

private:
  int x_;
  int y_;
};

// Copy constructor is called when passing the argument in,
// but not called when returning because of RVO (Return Value Optimization)
Point Scale(Point p, int factor) {
  return Point(p.x() * factor, p.y() * factor);
}

void Foo(Point &x) {
  x = {1,2};
}
