/*
* This is a virtual slot machine system which contains
* three CSpinner objects and one CMoney object
* Using a terminal menu system, this object allows users to:
*	- add credits using discrete units of currency
*	- play using number of credits 1-3
*	- cash out credits into quarters
* 	- exit the system (displaying machine loss or gain in USD)
* written by Stephen Szwiec, 5 February 2020 for CS161 at Minot State University
*/

/*revision v1.1, 11 February 2020
*	- bill functionality added
* 	- windows screen blanking now done in a less-vulnerable manner
*	- split runtime.cpp and CSlot.h from each other 
*/



#include <iostream> 
#include <ctype.h> //toupper(char)
#include "CMoney.h"
#include "CSpinner.h"

using namespace std;

class CSlot {
	private:
		CSpinner spinner1; //generates with 30,25,20,15,10 segment weights
		CSpinner spinner2; //for apple,orange,cherry,banana,peach respectively
		CSpinner spinner3; 
		CMoney cashier; //generates with 0 credits, 0 bills, and 500 quarters

		/*
		* function to wrap logic of cspinner payouts
		* 1, 2, or 3 quarters are used
		* if 1,2,or3xCherries are spun, then: x1, x2, or x20 used credits added
		* if 3xApple are spun, then: 4, 8, or 16 credits added
		* if 3xOrange are spun, then: 10, 20, or 30 credits added
		* if 3xBanana are spun, then: 50, 75, or 100 credits added
		* if 3xPeach are spun, then: 250, 500, or 750 credits added
		*/
		int genPayout(int creditsIn) {
			if( spinner1 == spinner2 && spinner2 == spinner3 ) {
				if (spinner1 == "Apple") { 
					if(creditsIn == 1) {
						return 4;
					}
					if(creditsIn == 2) {
						return 8;
					}
					if(creditsIn == 3) {
						return 16;
					}
				}
				else if (spinner1 == "Orange") {
					if(creditsIn == 1) {
						return 10;
					}
					if(creditsIn == 2) {
						return 20;
					}
					if(creditsIn == 3) {
						return 30;
					}
				}
				else if (spinner1 == "Banana") {
					if(creditsIn == 1) {
						return 50;
					}
					if(creditsIn == 2) {
						return 75;
					}
					if(creditsIn == 3) {
						return 100;
					}
				}
				else if (spinner1 == "Peach") {
					if(creditsIn == 1) {
						return 250;
					}
					if(creditsIn == 2) {
						return 500;
					}
					if(creditsIn == 3) {
						return 750;
					}
				}
				else if (spinner1 == "Cherry") {
					return creditsIn*20;
				}
			}
			else {
				//count number of cherries (inefficient)
				unsigned int numCherries = 0;
				if(spinner1 == "Cherry") {
					numCherries++;
				}
				if(spinner2 == "Cherry") {
					numCherries++;
				}
				if(spinner3 == "Cherry") {
					numCherries++;
				}
				//return money based on input and cherries
				if(numCherries == 1) {
					return creditsIn;
				} 
				else if(numCherries == 2) {
					return creditsIn*2;
				}
				else{
					return 0; //should reach this statement if no other payouts exist
				}
			}
		}

		//function to make the menu system less of an eyesore
		void genMenu(int pInput) { //expects payout input
			cout << "QUARTER SLOT MACHINE" << endl;
			cout << endl;
			cout << "Please select one of the following options -" << endl;
			cout << "Q: \t Quarter" << endl;
			cout << "O: \t One Dollar" << endl;
			cout << "F: \t Five Dollars" << endl;
			cout << "T: \t Ten Dollars" << endl;
			cout << "1: \t Play one quarter \t \t \t Credits- " << cashier.getCredits() << endl;
			cout << "2: \t Play two quarters \t \t \t Last Payoff- " << pInput << endl;
			cout << "3: \t Play three quarters" << endl;
			cout << "4: \t Cash out" << endl;
			cout << "5: \t Exit program" << endl;
			cout << endl;
			cout << "Last Spin ->";
			show();
		}

		//randomize the slot machine spinner state
		void spin() {
			spinner1.spin();
			spinner2.spin();
			spinner3.spin();
		}

		//utility function to print all three spinners
		void show() {
			cout << spinner1 << spinner2 << spinner3 << endl;
		}

	public:
		//utility function to properly clear the terminal
		void displayClear() {
			cout << "\033c" << endl;

		}

		//utility function to create visual break
		void displayBreak() {
			cout << string(80, '=') << endl;
		}

		//function to return a single character when someone facerolls on keyboard
		char inputHandler() {
			char input;
			cin.get(input);
			return toupper(input); 
		}

		//this is where the magic happens
		void run() {
			bool isRunning = true; //local variable to tell following do loop to continue
			int lastPayoff= 0; //local variable saving last non-zero payoff
			char userSelection = '\0'; //set this to null to ward off evil
			displayClear(); //clear the terminal before we display menu

			do {
				//print the main menu
				displayBreak();
				genMenu(lastPayoff);
				displayBreak(); 

				//input one char
				userSelection = inputHandler();
				cin.clear();

				//clear the terminal again for redraw 
				displayClear(); 

				//test the char versus switch and do something
				switch(userSelection) {
					case 'Q':
						cashier.addCredits(1); //adds a credit
						cashier.addQuarters(1); //adds a quarter
						break;

					case 'O':
						cashier.addCredits(4);
						cashier.addBills(1); //adds credits, but no quarters
						break;

					case 'F':
						cashier.addCredits(20);
						cashier.addBills(5);
						break;

					case 'T':
						cashier.addCredits(40);
						cashier.addBills(10);
						break;

					case '1':
						//if playable state, run a game with 1 credit parameters
						if(cashier.isPlayable(1)) { 
							cashier.removeCredits(1);
							spin();
							displayBreak();
							show();
							//it genuinely bothers me to read "you won 1 credits!" 
							if(genPayout(1) > 0 && genPayout(1) != 1) {
								cashier.addCredits(genPayout(1));
								lastPayoff = genPayout(1);
								cout << "Congrats! You won " << genPayout(1) << " credits!" << endl;
								}
							else if (genPayout(1) == 1) {
								cashier.addCredits(1);
								lastPayoff = 1;
								cout << "Congrats! You won 1 credit!" << endl;
								}
							else {
								cout << "Alas, this is not a winner." << endl;
								lastPayoff = 0; 
							}
						}
						else { //otherwise remind user this requires credits 
							cout << "Please add more money to receive play credits." << endl;
						}
						break;

					case '2':
						if(cashier.isPlayable(2)) {
							cashier.removeCredits(2);
							spin();
							displayBreak();
							show();
							if(genPayout(2) > 0) {
								cashier.addCredits(genPayout(2));
								lastPayoff = genPayout(2);
								cout << "Congrats! You won " << genPayout(2) << " credits!" << endl;
								}
							else {
								cout << "Alas, this is not a winner." << endl;
							}
						}
						else {
							cout << "Please add more money to receive play credits." << endl;
							lastPayoff = 0;
						}
						break;

					case '3':
						if(cashier.isPlayable(3)) {
							cashier.removeCredits(3);
							spin();
							displayBreak();
							show();
							if(genPayout(3) > 0) {
								cashier.addCredits(genPayout(3));
								lastPayoff = genPayout(3);
								cout << "Congrats! You won " << genPayout(3) << " credits!" << endl;
								}
							else {
								cout << "Alas, this is not a winner." << endl;
								lastPayoff = 0; 
							}
						}
						else {
							cout << "Please add more money to receive play credits." << endl;
						}
						break;

					case '4':
						displayBreak();
						if(cashier.isTooLow()) { //if we don't have enough quarters, tell user
							cout << "Please get a cashier to collect your prize earnings." << endl;
						}
						else if (cashier.getCredits() == 0) { //remind user they are being insipid
							cout << "You have no credits to pay out." << endl;
						}
						else {
							cashier.removeQuarters(cashier.getCredits());
							cout << "Paid out " << cashier.getCredits() << " quarters!" << endl;
							cashier.setCredits(0);
						}
						break;

					case '5':
						isRunning = false;
						displayBreak();
						if(cashier.getQuarters() - 500 == 0) {
							cout << "This slot machine neither lost nor gained quarters this run." << endl;
						}
						if(cashier.getQuarters() - 500 > 0) {
							cout << "This slot machine gained " << (cashier.getQuarters() - 500) << " quarters this run." << endl;
						}
						if(cashier.getQuarters() - 500 < 0) {
							cout << "This slot machine lost " << (500 - cashier.getQuarters()) << " quarters this run." << endl;
						}
						displayBreak();
						if(cashier.getQuarters() + 4*cashier.getBills() - 500 == 0) {
							cout << "This slot machine broke even this run." << endl;
						}
						if(cashier.getQuarters() + 4*cashier.getBills() - 500 > 0) {
							cout << "This machine gained $" << ((((float)cashier.getQuarters() + 4*(float)cashier.getBills()) - 500.0)/4.0) << " this run." << endl;

						}
						if(cashier.getQuarters() + 4*cashier.getBills() - 500 < 0) {
							cout << "This machine lost $" << ((500.0 - (float)cashier.getQuarters() + 4*(float)cashier.getBills())/4.0) << " this run." << endl;  
						}
						break;

					default:
						break;
				} 

			//clear cin buffer to prevent additional loops when multiple chars entered 
			cin.clear();
			cin.ignore(256, '\n');

			} while(isRunning == true); //end of do loop 
		} //end of run()
}; //end of CSlot class definition

int main() {
	CSlot machine;
	machine.run();
	return 0; 
}
