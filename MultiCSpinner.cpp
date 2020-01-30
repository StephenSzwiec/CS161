#include <iostream>
#include <time.h> //rand()
#include <bits/stdc++.h>
#include <vector> 
#include <iomanip> //setw()
#include <string> 
 
using namespace std;

//creates a cspinner object, which represents the randomness of a weighted percentile, like a spinner
class Cspinner {
	private:
		unsigned int currentSegment = 0; //initialize to zero to avoid evils associated with new ints 
		const string segmentNames[5] = {"Apple","Orange","Cherry","Banana","Peach"};
		std::vector<int> segmentWeights;

	public:
		//default constructor sets certain probabilities as per assignment
		Cspinner() {
			segmentWeights = {30,25,20,15,10};
		}
		//overload of constructor provides different weights than default per segment
		Cspinner(int a, int b, int c, int d, int e) {
			if(a + b + c + d + e == 100) {
				segmentWeights = {a,b,c,d,e};
			}
			else {
				cout << "Error initializing cspinner variable" << endl;
			}
		}

		//spin randomizes the currentSegment based on segment weights 
		void spin() {

			int i = rand() % 100 + 1; //generate int from 1 to 100
			int j = 0;
			while ( j < 5 && i > 0) {
				i = i - segmentWeights[j];
				if( i <= 0 ) { 
					currentSegment = j;
				}
				j++; 
			} 
		}

		//show prints out the segmentName referenced by currentSegment
		//superceded by redirection into stdout of class objects
/*		void show() {
*			cout << segmentNames[currentSegment] << " ";
*		}
*/

//This is where I would just declare "friend:" if C++ wasn't so inconsistent

		//comparing two cspinner objects with == returns the truthiness of their current segments 
		friend bool operator == (Cspinner &cs1, Cspinner &cs2) {
			return cs1.currentSegment == cs2.currentSegment;
		}

		//comparing a cspinner with an array of strings called segmentName and compares against an array of type char
		friend bool operator == (Cspinner &cs1, string tempString) {
			//compare segment name to string literal
			if (cs1.segmentNames[cs1.currentSegment].std::string::compare(tempString) != 0 ) {
				return false;
			}
			else {
				return true;
			}
		}
		//overload of << operator to send current segment name to stdout
		friend ostream& operator << (ostream& out, Cspinner &cs1) {
			out << std::setw(10);
			out << cs1.segmentNames[cs1.currentSegment];
			return out; 
		}
};

int main()
{
	//initialize randomness
	srand(time(NULL));
	//create spinners 
	Cspinner w1;
	Cspinner w2;
	Cspinner w3(80,5,5,5,5);
	//spin and show each spinner once per line
	for (int x = 0; x <= 9; x++) {
		w1.spin();
		w2.spin();
		w3.spin();
		cout << w1 << w2 << w3;
        if(w1 == w2 && w2 == w3) {
                    if (w1 == "Apple") { 
                    	cout  << "  (All Apples)" << endl;
                    }
                    else if (w1 == "Orange") {
                    	cout << "  (All Oranges)" << endl;
                    }
                    else if (w1 == "Cherry") {
                    	cout <<  "  (All Cherries) " << endl;
                    }
                    else if (w1 == "Banana") {
                    	cout << "  (All Bananas) " << endl;
                    }
                    else { cout  <<  "  (All Peaches)" << endl; }
                }
		else {
			cout << endl; 
		}
	}
	//wait for additional input before exiting terminal on windows
	cin.ignore();
	//return 0 to operating system
	return 0;
}
