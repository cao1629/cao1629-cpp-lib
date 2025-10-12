#pragma once
#include <iostream>

namespace cao1629 {


class Point {

public:
  Point(int x, int y): x_(x), y_(y) {
    std::cout << "Point's Constructor" << std::endl;
  }

  ~Point() {
    std::cout << "Point's Destructor" << std::endl;
  }

  Point(const Point &other) {
    std::cout << "Point's Copy Constructor" << std::endl;
    x_ = other.x_;
    y_ = other.y_;
  }

  Point(Point &&other)  noexcept {
    std::cout << "Point's Move Constructor" << std::endl;
    x_ = other.x_;
    other.x_ = 0;
    y_ = other.y_;
    other.y_ = 0;
  }

  Point& operator=(const Point &other) {
    std::cout << "Point's Copy Assignment" << std::endl;
    if (this != &other) {
      x_ = other.x_;
      y_ = other.y_;
    }
    return *this;
  }

  Point& operator=(Point &&other) noexcept {
    std::cout << "Point's Move Assignment" << std::endl;
    if (this != &other) {
      x_ = other.x_;
      other.x_ = 0;
      y_ = other.y_;
      other.y_ = 0;
    }
    return *this;
  }

  std::string ToString() const;

private:
  int x_;
  int y_;
};

}