/*
* This is the CSpinner class object for use in a slot machine
* This class object uses 32bit Marsenne Twister with high-resolution clock
* to generate pseudorandom integers in a mathematically uniform manner
* it selects and displays fruit on a weighted random basis
* written by Stephen Szwiec, 5 February 2020 for CS161 at Minot State University
*/

#pragma once
#include <chrono> //use high-resolution clock to seed random number gen
#include <random> //replaces rand() with Mersenne Twister algorithm mt19937
#include <iomanip> //setw()
#include <string>
using namespace std;

//creates a cspinner object, which represents the randomness of a weighted percentile, like a spinner
class CSpinner {
	private:
		unsigned int currentSegment = 0; //initialize to zero to avoid evils associated with new ints
		const string segmentNames[5] = {"Apple","Orange","Cherry","Banana","Peach"};
		std::vector<int> segmentWeights;

	public:
		//default constructor sets certain probabilities as per assignment
		CSpinner() {
			segmentWeights = {30,25,20,15,10};
		}
		//overload of constructor provides different weights than default per segment
		CSpinner(int a, int b, int c, int d, int e) {
			if(a + b + c + d + e == 100) {
				segmentWeights = {a,b,c,d,e};
			}
			else {
				cout << "Error initializing cspinner variable" << endl;
			}
		}

		//spin randomizes the currentSegment based on segment weights 
		void spin() {
			// obtain a seed from the system clock, then feed into Marseene Twister 
   			unsigned seed = static_cast<int> (std::chrono::system_clock::now().time_since_epoch().count());
			mt19937 generator(seed);
			uniform_int_distribution<int> distribution(1, 100); //generate a distribution 1 - 100
			int i = distribution(generator);
			int j = 0;
			while ( j < 5 && i > 0) {
				i = i - segmentWeights[j];
				if( i <= 0 ) { 
					currentSegment = j;
				}
				j++;
			}
		}

		//comparing two cspinner objects with == returns the truthiness of their current segments 
		friend bool operator == (CSpinner &cs1, CSpinner &cs2) {
			return cs1.currentSegment == cs2.currentSegment;
		}

		//comparing a cspinner with an array of strings called segmentName and compares against an array of type char
		friend bool operator == (CSpinner &cs1, string tempString) {
			//compare segment name to string literal
			if (cs1.segmentNames[cs1.currentSegment].std::string::compare(tempString) != 0 ) {
				return false;
			}
			else {
				return true;
			}
		}
		//overload of << operator to send current segment name to stdout
		friend ostream& operator << (ostream& out, CSpinner &cs1) {
			out << std::setw(7);
			out << cs1.segmentNames[cs1.currentSegment];
			return out;
		}
};

