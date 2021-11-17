#pragma once
#include <iostream>
using namespace std;

class BaseError{
public:
	virtual void cry() = 0;
};

class StackEmptyError : public BaseError {
public:
	void cry(){
		clog << "Stack is empty!" << endl;
	}
};

class StackFullError : public BaseError {
public:
	void cry() {
		clog << "Stack is full!" << endl;
	}
};

