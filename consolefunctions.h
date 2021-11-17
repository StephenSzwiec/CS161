//Written by Stephen Szwiec 15 April 2020 for Minot State University CSCI 161 Computer Science II

//This class packages the functions I keep using for console IO
#pragma once
#include <iostream>
#include <string> //string handling 
//windows specific headers to make console IO pretty
#include <Windows.h>
#include <conio.h>
//the following make the "any" key work in unix
//#include <stdio.h>
//#include <termios.h>
//#include <unistd.h>
//#include <fcntl.h>
using namespace std;

//linux display clearing utility function
//void displayClear() {
//		cout << "\033c" << endl;
//}

//windows display clearing utility function
//utility function to properly clear the terminal in windows
void displayClear(HANDLE hConsole) {
	COORD coordScreen = { 0, 0 };
	DWORD cCharsWritten;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD dwConSize;
	if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) {
		return;
	}
	dwConSize = csbi.dwSize.X * csbi.dwSize.Y; //set the console size based on current window
	if (!FillConsoleOutputCharacter(hConsole, (TCHAR)' ', dwConSize, coordScreen, &cCharsWritten)) {
		//fill entire buffer with spaces 
		return;
	}
	if (!FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten)) {
		return;
	}
	SetConsoleCursorPosition(hConsole, coordScreen);
}

//utility function to create visual break
void displayBreak() {
	cout << string(40, '=') << endl;
}

//function to return a single character when someone facerolls on keyboard
char charHandler() {
	char input;
	cin.get(input);
	return toupper(input);
}

//function to return an integer from standard input when someone facerolls on keyboard
int intHandler() {
	int input;
	cin >> input;
	while (cin.fail()) { //error handling loop
		cout << "Error: invalid input" << endl;
		cin.clear();
		cin.ignore(256, '\n');
		cin >> input;
	}
	return input;
}

//function to return a single integer from standard input when someone facerolls on keyboard
//will only use the first input integer in a sequence
//for instance, if user enters "-3foo" like a dummy, we just return "3"
int singleIntHandler() {
	int input;
	cin >> input;
	while (cin.fail()) { //error handling loop
		cout << "Error: invalid input" << endl;
		cin.clear();
		cin.ignore(256, '\n');
		cin >> input;
	}
	if (input < 0) {
		input = input * -1;
	}
	while (input > 10) {
		input = input / 10;
	}
	return input;
}

//function to return a positive float from standard input when someone facerolls on keyboard
//for instance an input of "-43.5foo33" will return "43.5"
float posFloatHandler() {
	float input;
	cin >> input;
	while (cin.fail()) { //error handling loop
		cout << "Error: invalid input" << endl;
		cin.clear();
		cin.ignore(256, '\n');
		cin >> input;
	}
	if (input < 0) {
		input = input * -1;
	}
	return input;
}

//actual implementation of a 'press any key to continue' such that it is unix specific
//code example credited to Vinay Sajip
// int kbhit(void)
// {
//   struct termios oldt, newt;
//   int ch;
//   int oldf;
//
//   tcgetattr(STDIN_FILENO, &oldt);
//   newt = oldt;
//   newt.c_lflag &= ~(ICANON | ECHO);
//   tcsetattr(STDIN_FILENO, TCSANOW, &newt);
//   oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
//   fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
//
//   ch = getchar();
//
//   tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
//   fcntl(STDIN_FILENO, F_SETFL, oldf);
//
//   if(ch != EOF)
//   {
//     ungetc(ch, stdin);
//     return 1;
//   }
//
//   return 0;
// }


