#include "Stack.h"
#include "consolefunctions.h"
#include <iostream>
using namespace std;
//get the handle to the current terminal
HANDLE currentTerminal = GetStdHandle(STD_OUTPUT_HANDLE);

//display main menu function
int mainMenu(){
	displayClear(currentTerminal);
	cout << "Main Menu" << endl;
	displayBreak();
	cout << "1) Add an item to the integer stack" << endl;
	cout << "2) Add an item to the character stack" << endl;
	cout << "3) Remove and display top item of integer stack" << endl;
	cout << "4) Remove and display top item of character stack" << endl;
	cout << "5) Exit program" << endl;
	cout << "Choice-> ";
	return singleIntHandler();
}

//display submenu function
char subMenu(){
	displayClear(currentTerminal);
	cout << "A) Throw away new item." << endl;
	cout << "B) Throw away top item." << endl;
	cout << "C)Throw away bottom item." << endl;
	cout << "Choice-> ";
	return charHandler();
}

//utility function to clear input
void flushInput() {
	fflush(stdin);
	cin.ignore();
	puts("Press any key to continue.");
	while (! _kbhit()) {
		;
	}
}

int main(){
	Stack<int> intStack;
	Stack<char> charStack;
	int choice;
	do{
		choice = mainMenu();
		switch (choice){
			case 1:
			{
				int input;
				cout << "Add what int to stack? ->";
				input = intHandler();
				try {
					intStack.push(input);
					flushInput();
					break;
				}
				catch(BaseError* e){
					char subChoice;
					bool hasChosen = false;
					do{
						subChoice = subMenu();
						if(subChoice == 'A'){
							hasChosen = true;
							//nothing more to be done here, let 'input' descope
							cout << "stack unchanged" << endl;
						}
						else if(subChoice == 'B'){
							hasChosen = true;
							cout << "removing " << intStack.pop() << " from top of stack." << endl;
							intStack.push(input);
						}
						else if(subChoice == 'C'){
							hasChosen = true;
							cout << "removing " << intStack.removeItemFromBottom() << " from bottom of stack." << endl;
							intStack.push(input);
						}
					} while (hasChosen == false);
				}
				flushInput();
				break;
			}
			case 2:
			{
				char input;
				cout << "Add what character to stack? ->";
				input = charHandler();
				try {
					charStack.push(input);
					flushInput();
					break;
				}
				catch(BaseError* e){
					char subChoice;
					bool hasChosen = false;
					while (hasChosen != true) {
						subChoice = subMenu();
						if(subChoice == 'A'){
							hasChosen = true;
							//nothing more to be done here, let 'input' descope
							cout << "stack unchanged" << endl;
						}
						else if(subChoice == 'B'){
							hasChosen = true;
							cout << "removing " << charStack.pop() << " from top of stack." << endl;
							charStack.push(input);
						}
						else if(subChoice == 'C'){
							hasChosen = true;
							cout << "removing " << charStack.removeItemFromBottom() << " from bottom of stack." << endl;
							charStack.push(input);
						}
					}
				}
				flushInput();
				break;
			}
			case 3:
			{
				if(intStack.empty() == true){
					cout << "Integer stack is already empty." << endl;
				}
				else {
					cout << intStack.pop() << " was removed from the stack." << endl;
				}
				flushInput();
				break; 
			}
			case 4:
			{
				if(charStack.empty() == true){
					cout << "Integer stack is already empty." << endl;
				}
				else {
					cout << charStack.pop() << " was removed from the stack." << endl;
				}
				flushInput();
				break; 
			}
			case 5:
			{
				cout << "Quitting..." << endl;
				break;
			}
			default:
			{
				break;
			}
		}
	} while (choice != 5);

	//clean up instack
	cout << "processing remainder of integer stack: " << endl;
	while (intStack.empty() != true){
			cout << intStack.pop() << endl;
	}
	cout << "processing remainder of character stack: " << endl;
	while (charStack.empty() != true){
			cout << charStack.pop() << endl;
	}
	puts("Stacks Cleared. Press any key to exit program.");
	while (!_kbhit()) {
		;
	}
	return 0;
}
