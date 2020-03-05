/*
* written by Stephen Szwiec, 26 February 2020 for CS161 at Minot State University
*/

#pragma once
#include "CCard.h"

class CPlayer {

private:
	unsigned int numCards; // keeps track of the number of cards in the players hand
	CCard hand[26]; // holds the cards that are in the players hand
	bool isComputer; // (true) computer and (false) human

public:

	//default constructor makes a 5 card hand with all Ace of Clubs
	//this is an abomination that should not exist in this world
	//but I need to do this with arrays instead of vectors for the extra points
	CPlayer() {
		numCards = 0;
		isComputer = true;
	}

	//constructor initializes with 5 cards, and is computer, requires a deck to build
	CPlayer(CDeck* deckIn) {
		numCards = 5; 
		for(int i = 0; i < 5; i++) {
			hand[i] = deckIn->dealCard(); 
		}
		isComputer = true;
	}

	//overloaded constructor to initialize with a number of cards, requires a deck to build, still a computer 
	CPlayer(CDeck* deckIn, int handSize) {
		numCards = handSize; 
		for(int i = 0; i < handSize; i++) {
			hand[i] = deckIn->dealCard(); 
		}
		isComputer = true;
	}

	//overloaded constructor to initialize with a cpu player option, requires a deck to build 
	CPlayer(CDeck* deckIn, bool cpu) {
		numCards = 5; 
		for(int i = 0; i < 5; i++) {
			hand[i] = deckIn->dealCard(); 
		}
		isComputer = cpu;
	}

	//overloaded constructor to initialize with both options, requires a deck to build
	CPlayer(CDeck* deckIn, int handSize, bool cpu) {
		numCards = handSize; 
		for(int i = 0; i < handSize; i++) {
			hand[i] = deckIn->dealCard(); 
		}
		isComputer = cpu;
	}

	//utility boilerplate function to swap two CCard objects
	void cardSwap(CCard *a, CCard *b) {
		CCard temp = *a;
		*a = *b;
		*b = temp;
	}

	//deal the next card into the hand
	void drawCard(CCard newCard) {
		hand[numCards++] = newCard;
	}

	//discard a card at an index, decrement number of cards after swapping 
	void discardCard(int input) {
		cardSwap(&hand[input], &hand[numCards - 1]); //swap these to prevent hand fragmentation
		numCards--;
	}

	//utility function to print out the hand 
	void printHand() {
		for(int i =0 ; i < numCards; i++) {
			cout << i+1 <<") ";
			cout << hand[i] << endl;
		}
	}

	//function to return a card in the hand at a positon
	CCard getCard(int input) {
		return hand[input];
	}

	//returns number of cards in the hand
	int getNumCards() {
		return numCards;
	}

	//sets number of cards in the hand
	void setNumCards(unsigned int input) {
		numCards = input;
	}

	//returns whether or not this player is a computer player
	bool isCpu() {
		return isComputer;
	}

	//sets the computer flag for player
	void setCPU(bool input) {
		isComputer = input;
	}
	
	//determines if a card can be played in CrazyEights
	bool canPlay(int index, CCard other) {
		return (hand[index] == other);
	}
};


