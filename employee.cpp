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

int main(int argc, char const *argv[]) {
  Employee *emp1 = new Employee(1, "John Doe", 50000, 30);
  Employee *emp2 = new Employee(2, "Jane Smith", 60000, 25);
  Employee *emp3 = new Employee(3, "Alice Johnson", 70000, 35);
  Employee *emp4 = new Employee(4, "Bob Brown", 80000, 40);
  Employee *emp5 = new Employee(5, "Charlie Davis", 90000, 28);

  std::vector<Employee *> employees;
  employees.push_back(emp1);
  employees.push_back(emp2);
  employees.push_back(emp3);
  employees.push_back(emp4);
  employees.push_back(emp5);

  auto result = std::max_element(employees.begin(), employees.end(),
    [](const Employee *e1, const Employee *e2) {
      return e1->salary() < e2->salary();
    });

  (*result)->Print();

  return 0;
}
