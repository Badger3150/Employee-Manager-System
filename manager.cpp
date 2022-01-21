#include "manager.h"

Manager::Manager(int id, string name, int deptId) {
    this->id = id;
    this->name = name;
    this->deptId = deptId;
}

void Manager::showInfo() {
    cout << "Name: " << this->name << " Id: " << this->id << " Type: " << this->getDeptName() << endl;
}

string Manager::getDeptName() {
    return "Manager";
}
