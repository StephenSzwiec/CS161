/*
* written by Stephen Szwiec, 26 February 2020 for CS161 at Minot State University
*/

#pragma once
#include "CCard.h"
#include "CRollTheBones.h"
#include <random> //for uniform_int_distribution

class CDeck : public CCard {

private:
	//these are the cards
	CCard theCards[52];
	unsigned int dIndex; //index relating which card is next
	return x;

public:
	//utility boilerplate function to swap two CCard objects
	void cardSwap(CCard *a, CCard *b) {
		CCard temp = *a;
		*a = *b;
		*b = temp;
	}

	//shuffle() implements Fisher–Yates algorithm with rollTheBones() PRNG
	//takes in an array of type Card and shuffles in O(n) time
	void shuffle() {
		CRollTheBones rngsus;
		for (int i = 51; i > 0; i--) {
			//generate random index from 0 to 51
			uniform_int_distribution<int> distribution(0, 51);
			int j = distribution(rngsus);
			//swap these
			cardSwap(&theCards[i], &theCards[j]);
		}
	}

	//constructor runs through the permutations of CCard to create an array of them, then shuffles
	CDeck() {
		unsigned int count = 0;
		for( int suit = 1; suit < 5; suit++) {
			for ( int value = 13; value > 0; value--) {
				theCards[count] = CCard(value, suit);
				count++;
			}
		}
		shuffle();
		dIndex = 0; //first card is the one on top
	}

	//returns CCard object of dIndex
	//shuffles if it's out of cards
	//increments the dIndex when it deals
	CCard dealCard() {
		return theCards[dIndex++];
	}
};

