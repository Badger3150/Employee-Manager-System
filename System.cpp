#include "System.h"
#include "worker.h"
#include "boss.h"
#include "manager.h"
#include "employee.h"

System::System() {
    ifstream ifs;
    ifs.open(FILENAME, ios::in);

    // test whether the file is open
    if (!ifs.is_open()) {
        cout << "No file exist!" << endl;
        this->emptyFile = true;
        this->empNum = 0;
        this->workerArr = nullptr;
        ifs.close();
        return;
    }
    // if we have the file but no content
	else if (ifs.get() == EOF)
	{
		cout << "Empty file!" << endl;
		this->empNum = 0;
		this->emptyFile = true;
		this->workerArr = nullptr;
		ifs.close();
		return;
	}
	// if we have file and it has content
    else {
        int num =  this->getEmpNum();
        cout << "The number of employees in the file is: " << num << endl;
        this->empNum = num;
        this->emptyFile = false;
        this->workerArr = new Worker*[num];
        initEmp();
    }
}


System::~System() {
    // because there is a pointer, so we has to delete by ourself
    if (this->workerArr != nullptr) {
    // base on the heap, so we need to delete them one by one
        for (int i = 0; i < this->empNum; ++i) {
            if (this->workerArr[i] != nullptr) delete this->workerArr[i];
        }
    }
    delete[] this->workerArr;
}

void System::showMenu() {
    cout << "********************************************" << endl;
    cout << "*******  Welcome to Manager System! ********" << endl;
    cout << "*************  0.Exit System  **************" << endl;
    cout << "*************  1.Add Employees  ************" << endl;
    cout << "************  2.Show Employees  ************" << endl;
    cout << "***********  3.Delete Employees  ***********" << endl;
    cout << "***********  4.Modify Employees  ***********" << endl;
    cout << "************  5.Find Employees  ************" << endl;
    cout << "************  6.Rank Employees  ************" << endl;
    cout << "*************  7.Clean All Doc  ************" << endl;
    cout << "********************************************" << endl;
    cout << endl;
}

void System::exitMenu() {
    cout << "Thanks for using the system!";
    exit(0);
}

void System::addWorker() {
    int num;
    cout << "How many workers you would like to add? ";
    cin >> num;

    if (num > 0) {
        // calculate how many workers in total
        int workerSize = this->empNum + num;

        Worker **newSapce = new Worker*[workerSize];

        if (this->workerArr != nullptr) {
            for (int i = 0; i < this->empNum; ++i) {
                newSapce[i] = this->workerArr[i];
            }
        }

        for (int i = this->empNum; i < workerSize; ++i) {
            int id;
            string name;
            int deptId;
            cout << "What is the id of the worker? ";
            cin >> id;

            cout << "What is the name of the worker? ";
            cin >> name;

            do {
                cout << "Which department is the worker belongs to? (Please enter the number)" << endl;
                cout << "0. boss" << endl;
                cout << "1. manager" << endl;
                cout << "2. employee" << endl;

                cin >> deptId;
            } while (deptId > 2 || deptId < 0);

            Worker* w = NULL;
            switch (deptId) {
            case 0 :
                w = new Boss(id, name, deptId);
                break;
            case 1 :
                w = new Manager(id, name, deptId);
                break;
            case 2 :
                w = new Employee(id, name, deptId);
                break;
            default:
                cout << "Invalid input." << endl;
                break;
            }
            newSapce[i] = w;

        }

        // delete original arr[can use vector to build later]
        delete[] this->workerArr;
        this->workerArr = newSapce;
        this->empNum = workerSize;
        // at this time, the file is not empty
        this->emptyFile = false;

        cout << "Success add " << num << " new workers!" << endl;

        this->saveFile();

    }
    else {
        cout << "Invalid number." << endl;
    }
    system("pause");
    system("cls");

}


void System::saveFile() {
    ofstream ofs;
    ofs.open(FILENAME, ios::out);
    for (int i = 0; i < this->empNum; i++)
	{
		ofs << this->workerArr[i]->id << " "
			<< this->workerArr[i]->name << " "
			<< this->workerArr[i]->deptId << endl;
	}
	ofs.close();
}

int System::getEmpNum() {
    ifstream ifs;
    ifs.open(FILENAME, ios::in);

    int id;
    string name;
    int deptId;

    int cntNum = 0;

    // ifs is a input stream, like cin >> has default separator is space, tab, transpose, ifs is same
    while (ifs >> id && ifs >> name && ifs >> deptId) {
        ++cntNum;
    }

    return cntNum;
}

void System::initEmp() {
    ifstream ifs;
    ifs.open(FILENAME, ios::in);

    int id;
    string name;
    int deptId;

    int index = 0;

    // same as the previous function
    while (ifs >> id && ifs >> name && ifs >> deptId) {
        // bcz deptId different will bring us different class, so we need to determine
        Worker* w = NULL;
        if (deptId == 0) {
            w = new Boss(id, name, deptId);
        }
        else if (deptId == 1) {
            w = new Manager(id, name, deptId);
        }
        else {
            w = new Employee(id, name, deptId);
        }
        this->workerArr[index] = w;
        index++;
    }
    return;
}

void System::showEmp() {
    if (this->emptyFile) {
        cout << "The file is empty or not exist"<< endl;
    }
    else {
        for (int i = 0; i < this->empNum; ++i) {
            this->workerArr[i]->showInfo();
        }
    }
}

int System::isExist(int id) {
    if (this->emptyFile) {
        cout << "The file is empty or not exist"<< endl;
    }
    else {
        for (int i = 0; i < this->empNum; ++i) {
            if (this->workerArr[i]->id == id) return i;
        }
    }
    return -1;
}

void System::deleteEmp() {
    if (this->emptyFile) {
        cout << "The file is empty or not exist"<< endl;
    }
    else {
        int id;
        cout << "Please enter the id of the employee that u like to delete: ";
        cin >> id;
        int index = isExist(id);
        if (index == -1) {
            cout << "Sorry, the id is invalid.";
        }
        else {
            for (int i = index; i < this->empNum - 1; i++)
			{
				this->workerArr[i] = this->workerArr[i+1];
			}
			this->empNum--;
			if (this->empNum == 0) {
                this->emptyFile = true;
			}
            this->saveFile(); // save the change
            cout << "Success delete!" << endl;
        }
    }
}

void System::modifyEmp() {
    if (this->emptyFile) {
        cout << "The file is empty or not exist"<< endl;
    }
    else {
        int id;
        cout << "Please enter the id of the employee that u like to modify: ";
        cin >> id;
        int index = isExist(id);
        if (index == -1) {
            cout << "Sorry, the id is invalid." << endl;
        }
        else {
            string content;
            cout << "what would you like to modify? ";
            cin >> content;
            if (content == "id") {
                int newId;
                cout << "which id would you like to change to? ";
                cin >> newId;
                this->workerArr[index]->id = newId;
            }
            else if (content == "name") {
                string newName;
                cout << "which name would you like to change to? ";
                cin >> newName;
                this->workerArr[index]->name = newName;
            }
            else if (content == "DeptId") {
                int newDeptId;
                cout << "which department id would you like to change to? ";
                cin >> newDeptId;
                this->workerArr[index]->deptId = newDeptId;
            }
            else {
                cout << "Sorry, you enter a wrong content, we don't have this attribute." << endl;
            }
            this->saveFile(); // save the change
            cout << "Success modify!" << endl;
        }
    }
}

void System::findEmp() {
    int choice;
    do {
        cout << "How would you like to find the employees? " << endl
        << "1. Search by id" << endl
        << "2. Search by name" << endl
        << "Please enter the corresponding number." << endl;
        cin >> choice;
    } while (choice != 1 && choice != 2);

    if (choice == 1) {
        int id;
        cout << "Please enter the id you would like to search: ";
        cin >> id;
        int index = isExist(id);
        if (index != -1) {
            this->workerArr[index]->showInfo();
        }
        else {
            cout << "Sorry, the id doesn't exist." << endl;
        }
    }

    else {
        string name;
        cout << "Please enter the name you would like to search: ";
        cin >> name;
        bool isFind = false;
        for (int i = 0; i < this->empNum; ++i) {
            if (this->workerArr[i]->name == name) {
                this->workerArr[i]->showInfo();
                isFind = true;
            }
        }
        if (!isFind) cout << "Sorry, the name doesn't exist." << endl;
    }
}

void System::sortEmp() {
    int choice;
    do {
        cout << "How would you like to sort the employees? " << endl
        << "1. Sort Ascend" << endl
        << "2. Sort Descend" << endl
        << "Please enter the corresponding number." << endl;
        cin >> choice;
    } while (choice != 1 && choice != 2);

}

void System::cleanEmp() {
    int choice;
    cout << "You would like to delete all employee? " << endl
    << "1. Yes" << endl
    << "2. No" << endl;
    cin >> choice;

    if (choice == 1) {
        if (this->emptyFile) {
            cout << "The file is empty already." << endl;
        }
        else {
            ofstream ofs(FILENAME, ios::trunc);
            ofs.close();

            if (this->workerArr != nullptr) {
                // base on the heap, so we need to delete them one by one
                for (int i = 0; i < this->empNum; ++i) {
                    if (this->workerArr[i] != nullptr) delete this->workerArr[i];
                }
            }
            this->empNum = 0;
            delete[] this->workerArr;
            this->workerArr = nullptr;
            this->emptyFile = true;
            cout << "Success Delete!" << endl;
        }
    }

}
