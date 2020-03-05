
/*
* written by Stephen Szwiec, 26 February 2020 for CS161 at Minot State University
*/

#pragma once
#include "CPlayer.h"
#include "CDeck.h" 
#include <stdio.h>

//the following make the "any" key work in unix
#include <termios.h> 
#include <unistd.h>
#include <fcntl.h>

//windows specific headers
//#include <string>
//#include <Windows.h>
//#include <conio.h>

class CCrazyEights {
private:
	CCard topCard; //this is the top card on the stack
	CDeck gameDeck;  //deck from which new cards are drawn
	CPlayer* players; //dynamically sized array for players
	//zero-initialized to prevent tomfoolery
	unsigned int numberPlayers = 0;
	unsigned int numberCPU = 0;
	unsigned int currentTurn = 0;
	int userSelection = '\0';
	bool hasAnyoneWon = false;
	//windows.h method to handle current terminal window
	//HANDLE currentTerminal = GetStdHandle(STD_OUTPUT_HANDLE);

public:
	
	//utility function to properly clear the terminal in unix
	void displayClear() {
		cout << "\033c" << endl;
	}

	//utility function to properly clear the terminal in windows
	// void displayClear(HANDLE hConsole) {
	// 	COORD coordScreen = { 0, 0 };
	// 	DWORD cCharsWritten;
	// 	CONSOLE_SCREEN_BUFFER_INFO csbi;
	// 	DWORD dwConSize; 
	// 	if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) {
	// 		return;
	// 	}
	// 	dwConSize = csbi.dwSize.X * csbi.dwSize.Y; //set the console size based on current window
	// 	if(!FillConsoleOutputCharacter(hConsole, (TCHAR) ' ', dwConSize, coordScreen, &cCharsWritten)) {
	// 		//fill entire buffer with spaces 
	// 		return;
	// 	}
	// 	if (!FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten)) {
	// 		return;
	// 	}
	// 	SetConsoleCursorPosition(hConsole, coordScreen);
	// }

	//utility function to create visual break
	void displayBreak() {
		cout << string(80, '=') << endl;
	}

	//function to return a single integer from standard input when someone facerolls on keyboard
	int inputHandler() {
		char input;
		cin >> input;
		return input - '0';
	}

	//sick Unicode graphics that don't work on windows
	void splashScreen() {
						cout << "▄▄      ▄▄           ▄▄▄▄                                                       " << endl;
						cout << "██      ██           ▀▀██                                                       " << endl;
						cout << "▀█▄ ██ ▄█▀  ▄████▄     ██       ▄█████▄   ▄████▄   ████▄██▄   ▄████▄            " << endl;
						cout << " ██ ██ ██  ██▄▄▄▄██    ██      ██▀    ▀  ██▀  ▀██  ██ ██ ██  ██▄▄▄▄██           " << endl;
						cout << " ███▀▀███  ██▀▀▀▀▀▀    ██      ██        ██    ██  ██ ██ ██  ██▀▀▀▀▀▀           " << endl;
						cout << " ███  ███  ▀██▄▄▄▄█    ██▄▄▄   ▀██▄▄▄▄█  ▀██▄▄██▀  ██ ██ ██  ▀██▄▄▄▄█           " << endl;
						cout << " ▀▀▀  ▀▀▀    ▀▀▀▀▀      ▀▀▀▀     ▀▀▀▀▀     ▀▀▀▀    ▀▀ ▀▀ ▀▀    ▀▀▀▀▀            " << endl;
						cout << "                                                                                " << endl;
						cout << "                                                                                " << endl;
						cout << "                                                                                " << endl;
						cout << "                                   ▄▄▄▄                                   " << endl;
						cout << "   ██                           ██▀▀▀▀█                                         " << endl;
						cout << " ███████    ▄████▄             ██▀        ██▄████   ▄█████▄  ████████  ▀██  ███" << endl; 
						cout << "   ██      ██▀  ▀██            ██         ██▀       ▀ ▄▄▄██      ▄█▀    ██▄ ██  " << endl;
						cout << "   ██      ██    ██            ██▄        ██       ▄██▀▀▀██    ▄█▀       ████▀  " << endl;
						cout << "   ██▄▄▄   ▀██▄▄██▀             ██▄▄▄▄█   ██       ██▄▄▄███  ▄██▄▄▄▄▄     ███   " << endl;
						cout << "    ▀▀▀▀     ▀▀▀▀                 ▀▀▀▀    ▀▀        ▀▀▀▀ ▀▀  ▀▀▀▀▀▀▀▀     ██    " << endl;
						cout << "                                                                         ███ " << endl;
						cout << "                                                                                " << endl;
						cout << "                                                                                " << endl;
    	  				cout << "▄▄▄▄▄▄▄▄     ██               ▄▄                                     " << endl;
	 	   			cout << "██▀▀▀▀▀▀     ▀▀               ██          ██                         " << endl;
	 	   			cout << "██         ████      ▄███▄██  ██▄████▄  ███████   ▄▄█████▄           " << endl;
	 	   			cout << "███████      ██     ██▀  ▀██  ██▀   ██    ██      ██▄▄▄▄ ▀           " << endl;
	 	   			cout << "██           ██     ██    ██  ██    ██    ██       ▀▀▀▀██▄           " << endl;
	 	   			cout << "██▄▄▄▄▄▄  ▄▄▄██▄▄▄  ▀██▄▄███  ██    ██    ██▄▄▄   █▄▄▄▄▄██           " << endl;
	 	   			cout << "▀▀▀▀▀▀▀▀  ▀▀▀▀▀▀▀▀   ▄▀▀▀ ██  ▀▀    ▀▀     ▀▀▀▀    ▀▀▀▀▀▀            " << endl;
	 	           	cout << "                     ▀████▀▀            " << endl;
						cout << endl;
						cout << "Press any key to begin!" << endl;
	}

	//sick ASCII graphics that do work on windows (optimized for widescreens)
	// void splashScreen() {
	// 	cout<<"    WWWWWWWW                           WWWWWWWW             lllllll                                                                                            tttt "<<endl;
	// 	cout<<"    W::::::W                           W::::::W             l:::::l                                                                                         ttt:::t "<<endl;
	// 	cout<<"    W::::::W                           W::::::W             l:::::l                                                                                         t:::::t "<<endl;
	// 	cout<<"    W::::::W                           W::::::W             l:::::l                                                                                         t:::::t "<<endl;
	// 	cout<<"     W:::::W           WWWWW           W:::::Weeeeeeeeeeee   l::::l    cccccccccccccccc  ooooooooooo     mmmmmmm    mmmmmmm      eeeeeeeeeeee         ttttttt:::::ttttttt      ooooooooooo"<<endl;
	// 	cout<<"      W:::::W         W:::::W         W:::::ee::::::::::::ee l::::l  cc:::::::::::::::coo:::::::::::oo mm:::::::m  m:::::::mm  ee::::::::::::ee       t:::::::::::::::::t    oo:::::::::::oo"<<endl;
	// 	cout<<"       W:::::W       W:::::::W       W:::::e::::::eeeee:::::el::::l c:::::::::::::::::o:::::::::::::::m::::::::::mm::::::::::me::::::eeeee:::::ee     t:::::::::::::::::t   o:::::::::::::::o"<<endl;
	// 	cout<<"        W:::::W     W:::::::::W     W:::::e::::::e     e:::::l::::lc:::::::cccccc:::::o:::::ooooo:::::m::::::::::::::::::::::e::::::e     e:::::e     tttttt:::::::tttttt   o:::::ooooo:::::o"<<endl;
	// 	cout<<"         W:::::W   W:::::W:::::W   W:::::We:::::::eeeee::::::l::::lc::::::c     cccccco::::o     o::::m:::::mmm::::::mmm:::::e:::::::eeeee::::::e           t:::::t         o::::o     o::::o"<<endl;
	// 	cout<<"          W:::::W W:::::W W:::::W W:::::W e:::::::::::::::::el::::lc:::::c            o::::o     o::::m::::m   m::::m   m::::e:::::::::::::::::e            t:::::t         o::::o     o::::o"<<endl;
	// 	cout<<"           W:::::W:::::W   W:::::W:::::W  e::::::eeeeeeeeeee l::::lc:::::c            o::::o     o::::m::::m   m::::m   m::::e::::::eeeeeeeeeee             t:::::t         o::::o     o::::o"<<endl;
	// 	cout<<"            W:::::::::W     W:::::::::W   e:::::::e          l::::lc::::::c     cccccco::::o     o::::m::::m   m::::m   m::::e:::::::e                      t:::::t    ttttto::::o     o::::o"<<endl;
	// 	cout<<"             W:::::::W       W:::::::W    e::::::::e        l::::::c:::::::cccccc:::::o:::::ooooo:::::m::::m   m::::m   m::::e::::::::e                     t::::::tttt:::::o:::::ooooo:::::o"<<endl;
	// 	cout<<"              W:::::W         W:::::W      e::::::::eeeeeeeel::::::lc:::::::::::::::::o:::::::::::::::m::::m   m::::m   m::::me::::::::eeeeeeee             tt::::::::::::::o:::::::::::::::o"<<endl;
	// 	cout<<"               W:::W           W:::W        ee:::::::::::::el::::::l cc:::::::::::::::coo:::::::::::oom::::m   m::::m   m::::m ee:::::::::::::e               tt:::::::::::ttoo:::::::::::oo"<<endl;
	// 	cout<<"                WWW             WWW           eeeeeeeeeeeeeellllllll   cccccccccccccccc  ooooooooooo  mmmmmm   mmmmmm   mmmmmm   eeeeeeeeeeeeee                 ttttttttttt    ooooooooooo"<<endl;
	// 	cout<<"            CCCCCCCCCCCCC                                                                               EEEEEEEEEEEEEEEEEEEEEE iiii                   hhhhhhh                    tttt                          !!!"<<endl;
	// 	cout<<"         CCC::::::::::::C                                                                               E::::::::::::::::::::Ei::::i                  h:::::h                 ttt:::t                         !!:!!"<<endl;
	// 	cout<<"       CC:::::::::::::::C                                                                               E::::::::::::::::::::E iiii                   h:::::h                 t:::::t                         !:::!"<<endl;
	// 	cout<<"      C:::::CCCCCCCC::::C                                                                               EE::::::EEEEEEEEE::::E                        h:::::h                 t:::::t                         !:::!"<<endl;
	// 	cout<<"     C:::::C       CCCCCrrrrr   rrrrrrrrr  aaaaaaaaaaaaa  zzzzzzzzzzzzzzzzyyyyyyy           yyyyyyy       E:::::E       EEEEEiiiiiii   ggggggggg   ggggh::::h hhhhh     ttttttt:::::ttttttt       ssssssssss  !:::!"<<endl;
	// 	cout<<"    C:::::C             r::::rrr:::::::::r a::::::::::::a z:::::::::::::::zy:::::y         y:::::y        E:::::E            i:::::i  g:::::::::ggg::::h::::hh:::::hhh  t:::::::::::::::::t     ss::::::::::s !:::!"<<endl;
	// 	cout<<"    C:::::C             r:::::::::::::::::raaaaaaaaa:::::az::::::::::::::z  y:::::y       y:::::y         E::::::EEEEEEEEEE   i::::i g:::::::::::::::::h::::::::::::::hht:::::::::::::::::t   ss:::::::::::::s!:::!"<<endl;
	// 	cout<<"    C:::::C             rr::::::rrrrr::::::r        a::::azzzzzzzz::::::z    y:::::y     y:::::y          E:::::::::::::::E   i::::ig::::::ggggg::::::gh:::::::hhh::::::tttttt:::::::tttttt   s::::::ssss:::::!:::!"<<endl;
	// 	cout<<"    C:::::C              r:::::r     r:::::r aaaaaaa:::::a      z::::::z      y:::::y   y:::::y           E:::::::::::::::E   i::::ig:::::g     g:::::gh::::::h   h::::::h    t:::::t          s:::::s  ssssss!:::!"<<endl;
	// 	cout<<"    C:::::C              r:::::r     rrrrrraa::::::::::::a     z::::::z        y:::::y y:::::y            E::::::EEEEEEEEEE   i::::ig:::::g     g:::::gh:::::h     h:::::h    t:::::t            s::::::s     !:::!"<<endl;
	// 	cout<<"    C:::::C              r:::::r          a::::aaaa::::::a    z::::::z          y:::::y:::::y             E:::::E             i::::ig:::::g     g:::::gh:::::h     h:::::h    t:::::t               s::::::s  !!:!!"<<endl;
	// 	cout<<"     C:::::C       CCCCCCr:::::r         a::::a    a:::::a   z::::::z            y:::::::::y              E:::::E       EEEEEEi::::ig::::::g    g:::::gh:::::h     h:::::h    t:::::t    tttttssssss   s:::::s !!!"<<endl;
	// 	cout<<"      C:::::CCCCCCCC::::Cr:::::r         a::::a    a:::::a  z::::::zzzzzzzz       y:::::::y             EE::::::EEEEEEEE:::::i::::::g:::::::ggggg:::::gh:::::h     h:::::h    t::::::tttt:::::s:::::ssss::::::s"<<endl;
	// 	cout<<"       CC:::::::::::::::Cr:::::r         a:::::aaaa::::::a z::::::::::::::z        y:::::y              E::::::::::::::::::::i::::::ig::::::::::::::::gh:::::h     h:::::h    tt::::::::::::::s::::::::::::::s !!!"<<endl;
	// 	cout<<"         CCC::::::::::::Cr:::::r          a::::::::::aa:::z:::::::::::::::z       y:::::y               E::::::::::::::::::::i::::::i gg::::::::::::::gh:::::h     h:::::h      tt:::::::::::tts:::::::::::ss !!:!!"<<endl;
	// 	cout<<"            CCCCCCCCCCCCCrrrrrrr           aaaaaaaaaa  aaazzzzzzzzzzzzzzzzz      y:::::y                EEEEEEEEEEEEEEEEEEEEEiiiiiiii   gggggggg::::::ghhhhhhh     hhhhhhh        ttttttttttt   sssssssssss    !!!"<<endl;
	// 	cout<<"                                                                                y:::::y                                                         g:::::g"<<endl;
	// 	cout<<"                                                                               y:::::y                                              gggggg      g:::::g"<<endl;
	// 	cout<<"                                                                              y:::::y                                               g:::::gg   gg:::::g"<<endl;
	// 	cout<<"                                                                             y:::::y                                                 g::::::ggg:::::::g"<<endl;
	// 	cout<<"                                                                            yyyyyyy                                                   gg:::::::::::::g"<<endl;
	// 	cout<<"                                                                                                                                        ggg::::::ggg"<<endl;
	// 	cout<<"                                                                                                                                           gggggg"<<endl;
	// 	cout<<"Press any key to begin!" << endl;
	// }

	void winScreen() {
		cout <<"     ######   #######  ##    ##  ######   ########     ###    ######## ##     ## ##          ###    ######## ####  #######  ##    ##  ######  ####"<<endl;
		cout <<"    ##    ## ##     ## ###   ## ##    ##  ##     ##   ## ##      ##    ##     ## ##         ## ##      ##     ##  ##     ## ###   ## ##    ## ####"<<endl;
		cout <<"    ##       ##     ## ####  ## ##        ##     ##  ##   ##     ##    ##     ## ##        ##   ##     ##     ##  ##     ## ####  ## ##       ####"<<endl;
		cout <<"    ##       ##     ## ## ## ## ##   #### ########  ##     ##    ##    ##     ## ##       ##     ##    ##     ##  ##     ## ## ## ##  ######   ##"<<endl;
		cout <<"    ##       ##     ## ##  #### ##    ##  ##   ##   #########    ##    ##     ## ##       #########    ##     ##  ##     ## ##  ####       ##"<<endl;
		cout <<"    ##    ## ##     ## ##   ### ##    ##  ##    ##  ##     ##    ##    ##     ## ##       ##     ##    ##     ##  ##     ## ##   ### ##    ## ####"<<endl;
		cout <<"     ######   #######  ##    ##  ######   ##     ## ##     ##    ##     #######  ######## ##     ##    ##    ####  #######  ##    ##  ######  ####"<<endl;
	}

	//actual implementation of a 'press any key to continue' such that it is unix specific
	//code example credited to Vinay Sajip
	int kbhit()	{
		struct termios oldt, newt;
		int ch;
		int oldf;
		tcgetattr (STDIN_FILENO, &oldt);
		newt = oldt;
		newt.c_lflag &= ~(ICANON | ECHO);
		tcsetattr(STDIN_FILENO, TCSANOW, &newt);
		oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
		fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
		ch = getchar();
		tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
		fcntl(STDIN_FILENO, F_SETFL, oldf);
		if(ch != EOF)
		{
			ungetc(ch, stdin);
			return 1;
		}
		return 0;
	}

	//show the main menu
	void startGame() {
		bool isInputError = true;
		cout << "How many players? (2-4):";
		numberPlayers = inputHandler();
		while(isInputError == true) { //error handling loop
			if(numberPlayers < 2 || numberPlayers > 4) {
				cout << "Error: 2 to 4 players. Please try again: " << endl;
				cin.clear();
				cin.ignore(256,'\n');
				cin >> numberPlayers;
			} 
			else if(cin.fail()) {
				cout << "Error: non-number input. please try again: " << endl;
				cin.clear();
				cin.ignore(256,'\n');
				cin >> numberPlayers; 
			}
			else {
				isInputError = false;
			}
		}
		/* we can have 0-3 CPU players in any game,
		 * and it will keep asking if we want any more
		 * until we say no or we are full
		 */
		bool moreCPU = true;
		while(numberPlayers - numberCPU > 1 && moreCPU == true) {
			char yesno;
			isInputError = true;
			cout << "Another computer opponent? (Y/N):";
			cin >> yesno;
			switch(yesno) {
				case 'Y':
				case 'y':
					numberCPU++;
					break;
				case 'N':
				case 'n':
					moreCPU = false;
					break;
				default:
					cin.ignore(256);
					cin.clear();
			}
		}
		//displayClear(currentTerminal);
		displayClear();
	}

	//Constructor method
	CCrazyEights() {
		splashScreen();
		//_getch();
		//displayClear(currentTerminal);
		cin.ignore();
		kbhit();
		displayClear();
		displayBreak();

		//collect game settings from the user
		startGame();

		//initialize an array of players
		players = new CPlayer[numberPlayers];

		//make new computer players behave as such
		for (int i = 0; i < (numberPlayers - numberCPU); i++) {
			players[i].setCPU(false);
		}

		//deal each players their cards
		if (numberPlayers == 2) {
			for (int i = 0; i < 7; i++) {
				for (int j = 0; j < numberPlayers; j++) {
					players[j].drawCard(gameDeck.dealCard());
				}
			}
		}
		else {
			for (int i = 0; i < 5; i++) {
				for (int j = 0; j < numberPlayers; j++) {
					players[j].drawCard(gameDeck.dealCard());
				}
			}
		}

		//set the top card so play can begin
		topCard = gameDeck.dealCard();
	}

	//Desructor method 
	~CCrazyEights(){
		delete[] players;
	}

	//if this was the last card in the hand, don't actually do anything except set the global win flag
	//otherwise play a card onto the stack then remove that same card from hand as normal
	void playCard(int index) {
		if ((players[currentTurn].getNumCards() - 1) == 0) {
				hasAnyoneWon = true; 
		}
		topCard = players[currentTurn].getCard(index - 1);
		cout << "played a " << players[currentTurn].getCard(index - 1) << endl;
		players[currentTurn].discardCard(index - 1);
		//if the card is an 8, then we get crazy
		if (topCard.getValue() == 8 && hasAnyoneWon == false) {
			//CPU are not tactical: select a pseudorandom suit
			if (players[currentTurn].isCpu() == true) {
				CRollTheBones anotherOne;
				uniform_int_distribution<int> distribution(1, 4);
				topCard.setSuit(distribution(anotherOne));
				cout << "CPU Player#" << currentTurn+1 << " placed an 8 and called its suit as " << topCard << endl;
				cout << "Crazy!" << endl;
			}
			//boring human input handling ahead
			else {
				cout << "Crazy Eight! Please call a new suit for the stack." << endl;
				cout << "1) Clubs" << endl << "2) Diamonds" << endl << "3) Hearts" << endl << "4) Spades" << endl;
				cout << "Your choice:";
				bool choiceMade = false;
				do {
					int choice = inputHandler();
					switch (choice) {
					case 1:
					case 2:
					case 3:
					case 4:
						topCard.setSuit(choice);
						choiceMade = true;
					default:
						cout << "Please try that again." << endl;
					}
				} while (choiceMade == false);
				cout << "placed an 8 and called its suit as " << topCard << endl;
				cout << "Crazy!" << endl;
			}
		}
	
	}

	//do a human turn for a player
	void humanTurn(int selector) {
		bool correctInput = false;
		int localUserInput;
		cout << "0) Draw a Card" << endl;
		players[selector].printHand();
		do { //godawful user error handler because humans are dumb
			cout << "Your choice: ";
			cin >> localUserInput;
			if (cin.fail()) { 
				cout << "Error: invalid input. Please try again." << endl;
				cin.clear();
				cin.ignore(256, '\n');
			}
			else if (localUserInput > players[selector].getNumCards()) { 
				cout << "Error: invalid input. Please try again." << endl;
				cin.clear();
				cin.ignore(256, '\n');
			}
			else if (localUserInput < 0) {
				cout << "Error: invalid input. Please try again." << endl;
				cin.clear();
				cin.ignore(256, '\n');
			}
			else if (localUserInput != 0) {
				if (players[selector].canPlay(localUserInput - 1, topCard) == false) {
					cout << "Error: " << players[selector].getCard(localUserInput - 1) << " does not play onto stack. Please try again." << endl;
					cin.clear();
					cin.ignore(256, '\n');
				}
				//the right card in the right place 
				else { 
					correctInput = true;
				}
			}
			//drawing a card 
			else {
				correctInput = true;
			}
		} while (!correctInput);
		if (localUserInput == 0) {
			players[currentTurn].drawCard(gameDeck.dealCard());
			cout << players[currentTurn].getCard(players[currentTurn].getNumCards()-1) << " was drawn." << endl;
			cout << "Press any key to continue...";
			//_getch();
			cin.get();
			kbhit();
		}
		else {
			playCard(localUserInput);
		}
	}

	//logic for the computer player: try each card in sequence, no tactics.
	void computerTurn(int selector) {
		bool playPossible = false;
		int foundIndex = 0;
		for(int i = 0; i < players[selector].getNumCards(); i++) {
			if (players[selector].canPlay(i, topCard) == true && playPossible == false) {
				playPossible = true;
				foundIndex = i+1;
			}
			else {
			}
		} 
		if (playPossible == true) {
			cout << "The CPU Player ";
			playCard(foundIndex);
		}
		else {
			cout << "The CPU Player draws a card" << endl;
			players[selector].drawCard(gameDeck.dealCard());
		}
		cin.ignore();
		kbhit();
	}

	//if the player is human, allow it to interface with the game
	//if the player is a computer, it will bumble through as best it can
	void turn() {
		cout << "The top card is " << topCard << "." << endl;
		cout << string(30, '-') << endl;
		cout << "It is Player " << currentTurn + 1 << "'s turn" << endl;
		if (players[currentTurn].isCpu() == true) {
			cout << "The computer player takes its turn..." << endl;
			computerTurn(currentTurn);
			cout << "Press any key to continue" << endl;
			//_getch();
			cin.ignore();
			kbhit();
		}
		else {
			humanTurn(currentTurn);
			cin.ignore();
			kbhit();
		}
		if (hasAnyoneWon == false) {
			//displayClear(currentTerminal);
			displayClear();
		}
	}
	
	//iterates through who has the turn, and gives them the turn until someone has won
	void run() {
		while (hasAnyoneWon == false) {
			bool endOfRound = false;
			turn();
			if (hasAnyoneWon == true) {
				winScreen();
				cout << "Player has no more cards and therefore " << currentTurn+1 << " has won!" <<  endl;
				//_getch();
				cin.ignore();
				kbhit();
			}
			if (numberPlayers == currentTurn + 1) {
				endOfRound = true;
			}
			if (endOfRound) {
				currentTurn = 0;
			}
			else {
				currentTurn++;
			}
		} 
	}

};

