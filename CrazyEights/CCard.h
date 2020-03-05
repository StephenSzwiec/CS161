
/*
* written by Stephen Szwiec, 26 February 2020 for CS161 at Minot State University
*/

#pragma once
#include <iostream>
using namespace std; 

enum TSuit {Clubs=1,Diamonds=2,Hearts=3,Spades=4}; //arranged alphabetically as in Bridge
const int ace = 1;
const int jack = 11;
const int queen = 12;
const int king = 13;

class CCard
{

friend ostream & operator <<(ostream &ls, CCard rs);
friend bool operator == (CCard &c1, CCard &c2);

private:
	int value;
	TSuit suit;

public:
	//default constructor makes an Ace of Clubs
	CCard() {
		value = 1;
		suit = Clubs;
	}

	//constructor takes integer value and human-readable suit name
	CCard(int newValue, TSuit newSuit) {
		value = newValue;
		suit = newSuit;
	}

	//constructor takes integer value and machine-readable suit number
	CCard(int newValue, int newSuit) {
		value = newValue;
		suit = static_cast<TSuit>(newSuit);
	}

	//arbitrarily set a card's value
	void setCard(int newValue, TSuit newSuit) {
		value = newValue;
		suit = newSuit;
	}

	//arbitrarily set a card's suit (for Crazy Eights suit call)
	void setSuit(TSuit newSuit) {
		suit = newSuit;
	}

	//arbitrarily set a card's suit using machine-readable int
	void setSuit(int newSuit) {
		suit = static_cast<TSuit>(newSuit);
	}

	//arbitrarily set a card's value
	void setValue(int newValue) {
		value = newValue;
	}

	//get the Tsuit as enum suit
	TSuit getTSuit() {
		return suit;
	}

	//get the suit as int
	int getSuit() {
		return suit;
	}

	//get the value 
	int getValue() {
		return value;
	}
};


// ostream & operator <<(ostream & ls, CCard rs)
// {
// 	switch (rs.value)
// 	{
// 	case ace:
// 		ls << "Ace";
// 		break;
// 	case jack:
// 		ls << "Jack";
// 		break;
// 	case queen:
// 		ls << "Queen";
// 		break;
// 	case king:
// 		ls << "King";
// 		break;
// 	default:
// 		ls << rs.value;
// 		break;
// 	}
// 	ls << " of";
// 	switch (rs.suit)
// 	{
// 	case Hearts:
// 		ls << " Hearts";
// 		break;
// 	case Diamonds:
// 		ls << " Diamonds";
// 		break;
// 	case Spades:
// 		ls << " Spades";
// 		break;
// 	case Clubs:
// 		ls << " Clubs";
// 		break;
// 	}
// 	return ls;
// }

ostream & operator <<(ostream & ls, CCard rs)
{
	switch (rs.value)
	{
		case ace:
			ls << "Ace";
			break;
		case jack:
			ls << "Jack";
			break;
		case queen: 
			ls << "Queen";
			break;
		case king:
			ls << "King";
			break;
		default:
			ls << rs.value;
			break;
	}
	
	//diamonds (♦), clubs (♣), hearts (♥) and spades (♠)
	ls << " of";
	switch (rs.suit)
	{
	case Hearts:
		ls << " ♥";
		break;
	case Diamonds:
		ls << " ♦";
		break;
	case Spades:
		ls << " ♠";
		break;
	case Clubs:
		ls << " ♣";
		break;
	}
	return ls;
}

//equality test specifically for CrazyEights
bool operator == (CCard &cs1, CCard &cs2) {
	if(cs1.getValue() == 8) { //CRAZY WWWWWW
		return true;
	}
	else if(cs1.getValue() == cs2.getValue()) {
		return true;
	}
	else if(cs1.getSuit() == cs2.getSuit()) {
		return true;
	}
	else {
		return false;
	}
}
