#pragma once
#include<iostream>
#include<string>
#include <fstream>
#define FILENAME "empFile.txt"
#include "worker.h"
using namespace std;

class System {
public:
    System();

    ~System();

    bool emptyFile;

    int empNum; //count the number of employees

    Worker **workerArr;

    // show the manage menu
    void showMenu();

    // exit the system
    void exitMenu();

    // add the worker
    void addWorker();

    // save the info into a file
    void saveFile();

    // get the number of employees in the file
    int getEmpNum();

    // initialized the employees in the file into the arr;
    void initEmp();

    // show the employees
    void showEmp();

    // find whether the employee exits
    int isExist(int id);

    // delete the employee
    void deleteEmp();

    // modify the employee
    void modifyEmp();

    // find the employee
    void findEmp();

    // sort the employee
    void sortEmp();

    // empty the file
    void cleanEmp();
};
