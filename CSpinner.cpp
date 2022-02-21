#include <iostream>
#include <time.h>
#include <bits/stdc++.h>
#include <vector>

using namespace std;

//creates a cspinner object, which represents the randomness of a weighted percentile, like a spinner
class Cspinner {
	private:
		unsigned int currentSegment = 0; //initialize to zero to avoid evils associated with new ints
		const string segmentNames[5] = {"apple","orange","cherry","banana","peach"};
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
		void show() {
			cout << segmentNames[currentSegment] << " ";
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
	for (int x=0;x<=9;x++) {
		w1.spin();
		w2.spin();
		w3.spin();
		w1.show();
		w2.show();
		w3.show();
		cout << endl;
	}
	//wait for additional input before exiting terminal on windows
	cin.ignore();
	//return 0 to operating system
	return 0;
}
