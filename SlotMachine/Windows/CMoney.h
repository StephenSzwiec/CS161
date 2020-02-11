
/*
* This is the CMoney object, providing functionality for credits and quarters
* written by Stephen Szwiec, 5 February 2020 for CS161 at Minot State University
*/

#pragma once
using namespace std;

//enum to shorthand
enum Currency {
	Q = 1,
	O = 4,
	F = 20,
	T = 40
};

class CMoney {
private:
	unsigned int credits;
	unsigned int quarters;
	unsigned int bills;

public:
	//constructor for class, default has 500 quarters inside as per technical reqs
	CMoney() {
		credits = 0;
		bills = 0;
		quarters = 500;
	}

	//constructor for class, adding a natural number of quarters to the machine
	CMoney(unsigned int input) {
		credits = 0;
		bills = 0;
		quarters = input;
	}

	//return the current number of credits
	int getCredits() {
		return credits;
	}

	//set an arbitrary number of credits for debugging purposes
	void setCredits(unsigned int input) {
		credits = input;
	}

	//add credits (actually used in slot machine runtime
	void addCredits(Currency input) {
		credits += input;
	}

	//add credits using int values rather than enum
	void addCredits(unsigned int input) {
		credits += input;
	}

	//removes credits (with error checking)
	void removeCredits(unsigned int input) {
		if (credits < input) {
			//do nothing 
		}
		else {
			credits -= input;
		}
	}

	int cashOut() {
		unsigned int temp = credits;
		credits = 0;
		return temp;
	}

	//set an arbitrary number of quarters for debugging purposes
	void setQuarters(unsigned int input) {
		quarters = input;
	}

	//return the current number of quarters
	int getQuarters() {
		return quarters;
	}

	//add quarters
	void addQuarters(unsigned int input) {
		quarters += input;
	}

	//removes quarters (with error checking) 
	void removeQuarters(unsigned int input) {
		if (quarters < input) {
			//do nothing
		}
		else {
			quarters -= input;
		}
	}

	//return the current number of bills
	int getBills() {
		return bills;
	}

	//set an arbitrary number of bills for debugging purposes
	void setBills(unsigned int input) {
		bills = input;
	}

	//add credits (actually used in slot machine runtime
	void addBills(Currency input) {
		bills += input;
	}

	//add credits using int values rather than enum
	void addBills(unsigned int input) {
		bills += input;
	}

	//removes credits (with error checking)
	void removeBills(unsigned int input) {
		if (bills < input) {
			//do nothing 
		}
		else {
			bills -= input;
		}
	}

	//utility function to tell if cashing out will not work
	//true if too low to pay out
	bool isTooLow() {
		return (credits > quarters);
	}

	//utility function to check if enough credits available for play
	//true if playable state
	bool isPlayable(int input) {
		return (input <= credits);
	}

	//operator overload to return credits via cout
	friend ostream& operator << (ostream& out, CMoney &input) {
		out << input.getCredits();
		return out;
	}
};