#include "employee.h"

Employee::Employee(int id, string name, int deptId) {
    this->id = id;
    this->name = name;
    this->deptId = deptId;
}

void Employee::showInfo() {
    cout << "Name: " << this->name << " Id: " << this->id << " Type: " << this->getDeptName() << endl;
}

string Employee::getDeptName() {
    return "employee";
}
