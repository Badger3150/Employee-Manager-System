#include "boss.h"

Boss::Boss(int id, string name, int deptId) {
    this->id = id;
    this->name = name;
    this->deptId = deptId;
}

void Boss::showInfo() {
    cout << "Name: " << this->name << " Id: " << this->id << " Type: " << this->getDeptName() << endl;
}

string Boss::getDeptName() {
    return "Boss";
}
