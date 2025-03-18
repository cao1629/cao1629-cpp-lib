#include <iostream>
#include <memory>

class Point {
public:


  // Constructor
  Point(int x, int y) : x_(x), y_(y) {
    std::cout << "Constructor called: " + ToString() << std::endl;
  }

  // Copy constructor
  Point(const Point &p) : x_(p.x_), y_(p.y_) {
    std::cout << "Copy constructor called" << std::endl;
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

  int x() const { return x_; }
  int y() const { return y_; }

private:
  int x_;
  int y_;
};

// Copy contructor is called when passing the argument in, 
// but not called when returning because of RVO (Return Value Optimization)
Point Scale(Point p, int factor) {
  return Point(p.x() * factor, p.y() * factor);
}


int main(int argc, char const *argv[]) {
  std::shared_ptr<Point> p1 = std::make_shared<Point>(1, 2);
  std::shared_ptr<Point> p2 = std::make_shared<Point>(3, 4);
  p2 = p1;
  return 0;
}

