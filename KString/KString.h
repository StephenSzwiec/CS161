#pragma once
#include <iostream>
using namespace std;

class KString {
	friend bool operator ==(KString &ls, KString &rs);
	friend bool operator ==(KString &ls, const char rs[]);
	friend bool operator <(KString &ls, KString &rs);
	friend bool operator <(KString &ls, const char rs[]);
	friend bool operator >(KString &ls, KString &rs);
	friend bool operator >(KString &ls, const char rs[]);
	friend ostream& operator <<(ostream& out, KString &rs);
	friend KString operator >>(istream& in, KString &ls);

	private:
		int length;
		char * charArray;
	public:

		//utility function to find the length of a char array like string.h's strlen
		int findLength(const char * input) {
			int length = 0; 
			bool keepGoing = true;
			while(keepGoing) {
				if(input[length] == 0) {
					keepGoing = false;
					return length;
				}
				length++;
			}
			//in case for some reason no null character is found
			return length; 
		}

		//default constructor creates an array with length zero and no data 
		KString() {
			length = 0;
			charArray = new char[0];
		}

		//one argument constructor taking in a C-type string
		KString(char const * input) {
			length = findLength(input);
			charArray = new char[length];
			for(int i = 0; i < length; i++) {
				charArray[i] = input[i];
			}
		}

		//copy constructor
		KString( const KString & input) {
			length = input.length;
			charArray = new char[length];
			for(int i = 0; i < length; i++) {
				charArray[i] = input.charArray[i];
			}
		}

		//deconstructor
		~KString() {
			delete[] charArray;
		}

		//returns length
		int getLength(){
			return length;
		}

		//overload of = operator, sets one KString equal to another
		KString operator =(const KString& rs) {
			length = rs.length;
			delete[] charArray;
			charArray = new char[length];
			for(int i = 0; i < length; i++) {
				charArray[i] = rs.charArray[i];
			}
			return *this;
		}

		//overload of + operator, allowing concatenation
		KString operator +(const KString& rs) {
			KString output;
			int temp = length;
			output.length = length + rs.length;
			//char accumulator[output.length] //allowed in GCC but not MSVS
			char* accumulator = new char[output.length];
			int i = 0; 
			for(int j = 0; j < length; j++) {
				accumulator[i] = charArray[j];
				i++;
			}
			for(int j = 0; j < rs.length; j++) {
				accumulator[i] = rs.charArray[j];
				i++;
			}

			delete[] output.charArray;
			output.charArray = new char[output.length];
			for(int k = 0; k < output.length; k++) {
				output.charArray[k] = accumulator[k];
			}
			return output;
		}

		//overload of += allowing concatenation via syntactic sugar 
		KString operator +=(const KString& rs) {
			KString output;
			int temp = length;
			output.length = length + rs.length;
			//char accumulator[output.length];
			char* accumulator = new char[output.length];
			int i = 0;
			for(int j = 0; j < length; j++) {
				accumulator[i] = charArray[j];
				i++;
			}
			for(int j = 0; j < rs.length; j++) {
				accumulator[i] = rs.charArray[j];
				i++;
			}
			delete[] output.charArray;
			output.charArray = new char[output.length];
			for(int k = 0; k < output.length; k++) {
				output.charArray[k] = accumulator[k];
			}
		}

		//overload of + allows arbitrary addition of characters to the end of the string
		KString operator +(const char& rs) {
			length++;
			//char accumulator[length]; //this just works in GCC
			char* accumulator = new char[length];
			for(int i = 0; i < length-1; i++) {
				accumulator[i] = charArray[i];
			}
			accumulator[length]= rs; 
			delete[] charArray;
			charArray = new char[length];
			for(int i = 0; i < length-1; i++) {
				charArray[i] = accumulator[i];
			}
		}

		//can be used for assignment
		char & operator [](int loc) {
			if (loc >= length){
				length = loc;
			}
			return charArray[loc-1];
		}

		//for accessing the charArray 
		const char operator [](int loc) const {
			if (loc > length)
			{
				return NULL;
			}
			return charArray[loc-1];
		}
};

		//comparing two KString objects with == returns true if every single char the same
		bool operator ==(KString &ls, KString &rs) {
			//don't even bother comparing if they aren't the same length
			if(ls.length != rs.length) {
				return false;
			}
			else {
				for(int i = 0; i < ls.length; i++) {
					if(ls.charArray[i] != rs.charArray[i]) {
						return false;
					}
				}
				return true;
			}
		}

		//comparing a KString with an array of char also returns true if every single char is the same
		bool operator ==(KString &ls, const char * rs) {
			if(ls.length != ls.findLength(rs)) {
				return false;
			}
			else {
				for(int i = 0; i < ls.length; i++) {
					if(ls.charArray[i] != rs[i]) {
						return false;
					}
				}
				return true;
			}
		}

		//comparing two KStrings, returns true if right side is longer
		bool operator <(KString &ls, KString &rs) {
			return ls.length < rs.length;
		}

		//comparing a KString and a C string, returns true if right side is larger
		bool operator <(KString &ls, const char rs[]) {
			return ls.length < ls.findLength(rs); 
		}

		//comparing two KStrings, returns true if left side is longer
		bool operator >(KString &ls, KString &rs) {
				return ls.length > rs.length;
		}

		//comparing a KString and a C string, returns true if left side is larger
		bool operator >(KString &ls, const char rs[]) {
			return ls.length < ls.findLength(rs);
		}

		//overload of << operator to send current segment name to stdout
		ostream& operator << (ostream& out, KString &rs) {
			for(int i = 0; i < rs.length; i++) {
				out << rs.charArray[i];
			}
			return out;
		}

		//overload of >> operator to accept input 
		KString operator >>(istream& in, KString &rs) {
			char tempArray[256];
			in >> tempArray;
			rs.length = rs.findLength(tempArray);
			rs.charArray = new char[rs.length];
			for(int i = 0; i < rs.length; i++) {
				rs.charArray[i] = tempArray[i];
			}
			return rs;
		}
