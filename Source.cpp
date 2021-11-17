//Written by Stephen Szwiec 15 April 2020 for Minot State University CSCI 161 Computer Science II
#include <iostream>
#include "CEmployee.h"
#include "consolefunctions.h"
using namespace std;

//create handle to current terminal window for better IO 
HANDLE currentTerminal = GetStdHandle(STD_OUTPUT_HANDLE);

//display HFE menu and contributing logic
CHourlyFTEmployee* HFEMenu() {
	char name[30];
	char id[30];
	float rate, hours;
	displayClear(currentTerminal);
	cout << "Enter new hourly fulltime employee data" << endl;
	displayBreak();
	cout << "name->";
	cin >> name;
	cout << "id->";
	cin >> id;
	cout << "rate->";
	rate = posFloatHandler();
	cout << "hours->";
	hours = posFloatHandler();
	CHourlyFTEmployee* r = new CHourlyFTEmployee(name, id, rate, hours);
	return r;
}

CSalariedFTEmployee* SFEMenu() {
	char name[30];
	char id[30];
	float salary;
	displayClear(currentTerminal);
	cout << "Enter new salaried fulltime employee data" << endl;
	displayBreak();
	cout << "name->";
	cin >> name;
	cout << "id->";
	cin >> id;
	cout << "salary->";
	salary = posFloatHandler();
	CSalariedFTEmployee* r = new CSalariedFTEmployee(name, id, salary);
	return r;
}

CCommissionedFTEmployee* CFEMenu() {
	char name[30];
	char id[30];
	float comm;
	float vol;
	displayClear(currentTerminal);
	cout << "Enter new commissioned fulltime employee data" << endl;
	displayBreak();
	cout << "name->";
	cin >> name;
	cout << "id->";
	cin >> id;
	cout << "commission percent->";
	comm = posFloatHandler();
	cout << "sales->";
	vol = posFloatHandler();
	CCommissionedFTEmployee* r = new CCommissionedFTEmployee(name, id, comm, vol);
	return r;
}

CSalariedCommissionedFTEmployee* SCFEMenu() {
	char name[30];
	char id[30];
	float salary;
	float comm;
	float vol;
	displayClear(currentTerminal);
	cout << "Enter new salaried commissioned fulltime employee data" << endl;
	displayBreak();
	cout << "name->";
	cin >> name;
	cout << "id->";
	cin >> id;
	cout << "salary->";
	salary = posFloatHandler();
	cout << "commission percent->";
	comm = posFloatHandler();
	cout << "sales->";
	vol = posFloatHandler();
	CSalariedCommissionedFTEmployee* r = new CSalariedCommissionedFTEmployee(name, id, salary, comm, vol);
	return r;
}

CHourlyPTEmployee* HPEMenu() {
	char name[30];
	char id[30];
	float rate, hours;
	displayClear(currentTerminal);
	cout << "Enter new hourly parttime employee data" << endl;
	displayBreak();
	cout << "name->";
	cin >> name;
	cout << "id->";
	cin >> id;
	cout << "rate->";
	rate = posFloatHandler();
	cout << "hours->";
	hours = posFloatHandler();
	CHourlyPTEmployee* r = new CHourlyPTEmployee(name, id, rate, hours);
	return r;
}

//display main menu function
int mainMenu() {
	displayClear(currentTerminal);
	cout << "Main Menu" << endl;
	displayBreak();
	cout << "1) Enter hourly fulltime employee" << endl;
	cout << "2) Enter salaried fulltime employee" << endl;
	cout << "3) Enter commissioned fulltime employee" << endl;
	cout << "4) Enter salaried & commissioned fulltime employee" << endl;
	cout << "5) Enter hourly parttime employee" << endl;
	cout << "6) Print checks for all employees" << endl;
	cout << "7) Print report of all employees" << endl;
	cout << "8) Update an employee's pay data" << endl;
	cout << "9) Exit program" << endl;
	cout << "Choice-> ";
	return singleIntHandler();
}

int main()
{
	CEmployee* empDB[100];
	int index = 0;
	int choice;
	do {
		choice = mainMenu();
		switch (choice) {
		case 1:
		{
			empDB[index] = HFEMenu();
			index++;
			fflush(stdin);
			cin.ignore();
			puts("Press any key to continue.");
			while (!_kbhit()) {
				;
			}
			break;
		}
		case 2:
		{
			empDB[index] = SFEMenu();
			index++;
			fflush(stdin);
			cin.ignore();
			puts("Press any key to continue.");
			while (!_kbhit()) {
				;
			}
			break;

		}
		case 3:
		{
			empDB[index] = CFEMenu();
			index++;
			fflush(stdin);
			cin.ignore();
			puts("Press any key to continue.");
			while (!_kbhit()) {
				;
			}
			break;
		}
		case 4:
		{
			empDB[index] = SCFEMenu();
			index++;
			fflush(stdin);
			cin.ignore();
			puts("Press any key to continue.");
			while (!_kbhit()) {
				;
			}
			break;
		}
		case 5:
		{
			empDB[index] = HPEMenu();
			index++;
			fflush(stdin);
			cin.ignore();
			puts("Press any key to continue.");
			while (!_kbhit()) {
				;
			}
			break;
		}
		case 6:
		{
			displayClear(currentTerminal);
			cout << "Printing Checks" << endl;
			displayBreak();
			for (int i = 0; i < index; i++) {
				empDB[i]->PrintCheck();
			}
			fflush(stdin);
			cin.ignore();
			puts("Press any key to continue.");
			while (!_kbhit()) {
				;
			}
			break;
		}
		case 7:
		{
			displayClear(currentTerminal);
			cout << "Employee Summary" << endl;
			displayBreak();
			for (int i = 0; i < index; i++) {
				cout << empDB[i] << endl;
			}
			fflush(stdin);
			cin.ignore();
			puts("Press any key to continue.");
			while (!_kbhit()) {
				;
			}
			break;
		}
		case 8:
		{
			displayClear(currentTerminal);
			char checkedID[30];
			int target = -1;
			cout << "Enter Employee ID-> ";
			cin >> checkedID;
			while (cin.fail()) { //error handling loop
				cout << "Error: invalid input" << endl;
				cin.clear();
				cin.ignore(256, '\n');
				cin >> checkedID;
			}
			for (int i = 0; i < index; i++) {
				char* temp = empDB[i]->getID();
				if (strcmp(temp, checkedID) == 0) {
					target = i;
				}
			}
			if (target == -1) {
				cout << "Employee not found." << endl;
			}
			if (target != -1) {
				CHourlyFTEmployee* hfe;
				hfe = dynamic_cast<CHourlyFTEmployee*>(empDB[target]);
				if (hfe) {
					cout << "modifying hourly fulltime employee " << empDB[target]->getID() << endl;
					cout << "new rate->";
					int rate = posFloatHandler();
					cout << "new hours->";
					int hours = posFloatHandler();
					hfe->updatePayData(rate, hours);
				}

				CSalariedFTEmployee* sfe;
				CCommissionedFTEmployee* cfe;
				CSalariedCommissionedFTEmployee* scfe;
				sfe = dynamic_cast<CSalariedFTEmployee*>(empDB[target]);
				cfe = dynamic_cast<CCommissionedFTEmployee*>(empDB[target]);
				scfe = dynamic_cast<CSalariedCommissionedFTEmployee*>(empDB[target]);
				if (scfe) {
					cout << "modifying salaried commissioned fulltime employee " << empDB[target]->getID() << endl;
					cout << "new salary->";
					int salary = posFloatHandler();
					cout << "new commmission percent->";
					int comm = posFloatHandler();
					cout << "new sales volume->";
					int vol = posFloatHandler();
					scfe->updatePayData(salary, comm, vol);
				}
				else if (sfe) {
					cout << "modifying salaried fulltime employee " << empDB[target]->getID() << endl;
					cout << "new salary->";
					int salary = posFloatHandler();
					sfe->updatePayData(salary);
				}
				else if (cfe) {
					cout << "modifying commissioned fulltime employee " << empDB[target]->getID() << endl;
					cout << "new commmission percent->";
					int comm = posFloatHandler();
					cout << "new sales volume->";
					int vol = posFloatHandler();
					cfe->updatePayData(comm, vol);
				}
				CHourlyPTEmployee* pfe;
				pfe = dynamic_cast<CHourlyPTEmployee*>(empDB[target]);
				if (pfe) {
					cout << "modifying hourly parttime employee " << empDB[target]->getID() << endl;
					cout << "new rate->";
					int rate = posFloatHandler();
					cout << "new hours->";
					int hours = posFloatHandler();
					pfe->updatePayData(rate, hours);
				}
			}
			fflush(stdin);
			cin.ignore();
			puts("Press any key to continue.");
			while (!_kbhit()) {
				;
			}
			break;
		}
		case 9:
		{
			cout << "Thank you for using CEmployee Database." << endl;
			fflush(stdin);
			cin.ignore();
			puts("Press any key to continue.");
			while (!_kbhit()) {
				;
			}
			break;
		}
		default:
		{
			break;
		}
		}
	} while (choice != 9);
	return 0;
}
