#include <algorithm>
#include <iostream>
#include <string>
#include <queue>

class Employee {
private:
  int id_;
  std::string name_;
  double salary_;
  int age_;

public:
  Employee(int id, const std::string &name, double salary, int age)
      : id_(id), name_(name), salary_(salary), age_(age) {
    // std::cout << "Constructor called for Employee: " << id_ << std::endl;
  }

  int id() const { return id_; }
  const std::string &name() const { return name_; }
  double salary() const { return salary_; }
  int age() const { return age_; }

  void Print() const {
    std::cout << "ID: " << id_ << ", Name: " << name_ << ", Salary: " << salary_
              << ", Age: " << age_ << std::endl;
  }

  // Copy constructor
  Employee(const Employee &other)
      : id_(other.id_), name_(other.name_), salary_(other.salary_) {
    // std::cout << "Copy constructor called" << std::endl;
  }

  // Assignment operator
  Employee &operator=(const Employee &other) {
    // std::cout << "Assignment operator called" << std::endl;
    if (this != &other) {
      id_ = other.id_;
      name_ = other.name_;
      salary_ = other.salary_;
      age_ = other.age_;
    }
    return *this;
  }
  // Destructor
  ~Employee() {
    // std::cout << "Destructor called for Employee: " << id_ << std::endl;
  }

  bool operator<(const Employee &other) const {
    return salary_ < other.salary_;
  }

};

