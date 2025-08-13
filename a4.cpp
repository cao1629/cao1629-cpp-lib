
#include "DataClass/employee.h"


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