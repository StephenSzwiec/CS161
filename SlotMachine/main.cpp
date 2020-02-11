/*
* written by Stephen Szwiec, 11 February 2020 for CS161 at Minot State University
*/

/*revision v1.0, 5 February 2020
*	- implemented Marsenne Twister for randomness in CSpinner
*	- implemented runtime and logic
*/

/*revision v1.1, 11 February 2020
*	- bill functionality added, including end of run auditing
* 	- windows screen blanking now done in a less-vulnerable manner
*	- split runtime.cpp and CSlot.h from each other 
*/
#incliude <iostream>
#include "CSlot.cpp"
using namespace std;

int main() {
	CSlot machine;
	machine.run();
	return 0; 
}
