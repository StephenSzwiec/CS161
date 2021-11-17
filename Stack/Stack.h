#pragma once
#include "BaseError.h"
#include "consolefunctions.h"
#include <iostream>
using namespace std;

//generic stack object, top is always 0th element
template<typename t>
class Stack{
	private:
		int size;
		int elements; 
		t* arr;
		BaseError* stackError;

	public:
		//constructor creates a new stack of size 5 by default
		Stack(){
			size = 5; 
			elements = 0; 
			arr = new t[size+1];
		}

		//constructor for arbitrary sizes
		Stack(unsigned int s){
			size = s;
			elements = 0;
			arr = new t[size+1];
		}

		//deconstructor 
		~Stack() {
			delete[] arr;
		}
		//copy constructor
		Stack(const Stack& input){
			size = input.size;
			elements = input.elements;
			arr = new t[size+1];
			for (int i = 0; i < size; i++){
				arr[i] = input.arr[i];
			}
		}

		//copy constructor for a stack and new size
        Stack(const Stack &input, int newSize) {
			size = newSize;
            elements = input.elements;
			arr = new t[size + 1];
			for (int i = 0; i < size; i++) {
				arr[i] = input.arr[i];
			}
		}

		//move constructor
		Stack(Stack&& input) {
			size = input.size;
			elements = input.elements;
			arr = new t[size+1];
			for (int i = 0; i < size; i++) {
				arr[i] = input.arr[i];
			}
			input.size = {};
			input.elements = {};
			delete[] input.arr;
		}

		//returns true if stack is empty
		bool empty() {
			if (elements == 0){
				return true;
			}
			else{ 
				return false;
			}
		}

		//adds an element to the top of the stack
		//throws exception and asks for more space if full
		void push(t item){
			try {
				if (elements == size){
					stackError = new StackFullError; 
					throw stackError; 
				}
				for (int i = elements; i >= 0; i--){
					swap(arr[i + 1], arr[i]);
				}
				arr[0] = item;
				elements++;
			}
			catch (BaseError* stackError) {
				StackFullError* sfe;
				sfe = dynamic_cast<StackFullError*>(stackError);
				if (sfe) {
					sfe->cry();
					cout << "Add capacity to stack? (Y/N)" << endl;
					bool hasChosen = false;
					while (hasChosen == false){
						char input = charHandler();
						if (input == 'Y'){
							hasChosen = true;
							int newSize = size + 5; 
							t* newArr = new t[newSize];
							for (int i = 0; i < elements; i++) {
								newArr[i + 1] = arr[i];
							}
							newArr[0] = item;
							elements++;
							delete[] arr;
							arr = newArr;
							size = newSize;
						}
						else if(input == 'N'){
							hasChosen = true;
							throw;
						}
					}
				}
			}
		}

		//returns the top item of a stack 
		//throws an exception if the stack is empty
		t pop(){
			try {
				if (empty()) {
					stackError = new StackEmptyError;
					throw stackError; 
				}
				t top = arr[0];
				for (int i = 0; i < elements; i++) {
					swap(arr[i], arr[i + 1]);
				}
				elements--;
				return top;
			}
			catch (BaseError* stackError) {
				StackEmptyError* see;
				see = dynamic_cast<StackEmptyError*>(stackError);
				if(see){
					see->cry();
				}
			}
		}

		//removes item from bottom and returns it
		t removeItemFromBottom() {
			try {
				if (empty()) {
					stackError = new StackEmptyError;
					throw stackError; 
				}
				t bottom = arr[elements-1];
				elements--;
				return bottom;
			}
			catch (BaseError* stackError) {
				StackEmptyError* see;
				see = dynamic_cast<StackEmptyError*>(stackError);
				if (see) {
					see->cry();
				}
			}
		}

		//utility function to print a stack
		void printStack(){
			for (int i = 0; i < elements; i++) {
				cout << "element " << i << ": " << arr[i] << endl;
			}
		}
};
