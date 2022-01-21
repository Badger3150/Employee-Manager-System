#include <iostream>
#include <string>
#include "System.h"
#include "employee.h"
#include "manager.h"
#include "worker.h"
#include "boss.h"
using namespace std;
int main()
{
    System s;
    int choice = 0;
    while (true) {
        s.showMenu();
        cout << "Choose the function: ";
        cin >> choice;
        switch (choice)
		{
		case 0: //exit
		    s.exitMenu();
			break;
		case 1: //add
		    s.addWorker();
			break;
		case 2: //display
		    s.showEmp();
			break;
		case 3: //delete
		    s.deleteEmp();
			break;
		case 4: //modify
		    s.modifyEmp();
			break;
		case 5: //find
		    s.findEmp();
			break;
		case 6: //sort
			break;
		case 7: //clean
		    s.cleanEmp();
			break;
		default:
			system("clf");
			break;
		}
		cout << endl;
		system("pause");
    }

	system("pause");

	return 0;
}
