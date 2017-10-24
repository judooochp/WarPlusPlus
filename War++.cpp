#include"stdafx.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <iomanip>
#include <windows.h> 

using namespace std;

//	Large Card Suits for A, K, Q, J
const string AceSPADE[7] = { "    /\\    ", "   //\\\\   ", "  //  \\\\  ", " // /\\ \\\\ ", "| \\//\\\\/ |", " \\_/||\\_/ ", "    __    " };
const string AceHEART[7] = { "  __  __  ", " / _\\/_ \\ ", "| < \\/ > |", " \\ \\  / / ", "  \\ \\/ /  ", "   \\  /   ", "    \\/    " };
const string AceCLUB[7] = { "    /\\    ", "   <<>>   ", "    \\/    ", " /\\ || /\\ ", "<<>>==<<>>", " \\/ || \\/ ", "    __    " };
const string AceDIAMOND[7] = { "    /\\    ", "   /  \\   ", "  / /\\ \\  ", " < <  > > ", "  \\ \\/ /  ", "   \\  /   ", "    \\/    " };

//	Medium Card Suits for corners
const string CornerSPADE[2] = { " ^ ", "(+)" };
const string CornerSPADE2[2] = { "(+)", " v " };
const string CornerHEART[2] = { "(V)", " v " };
const string CornerHEART2[2] = { " ^ ", "(^)" };
const string CornerCLUB[2] = { " o ", "o+o" };
const string CornerCLUB2[2] = { "o+o", " o " };
const string CornerDIAMOND[2] = { " /\\", " \\/" };
const string CornerDIAMOND2[2] = { " /\\", " \\/" };

//	Upside Down Symbols for radial "symmetry"
const string UpACE = " V";
const string UpTWO = " Z";
const string UpTHREE = " E";
const string UpFOUR = " h";
const string UpFIVE = " S";
const string UpSIX = " 9";
const string UpSEVEN = " L";
const string UpEIGHT = " 8";
const string UpNINE = " 6";
const string UpTEN = "0I";
const string UpJACK = " r";
const string UpQueen = " Q";
const string UpKING = " X";
const int line1 = 0;
const int line2 = 1;
const int line3 = 2;
const int line4 = 3;
const int line5 = 4;
const int line6 = 5;
const int line7 = 6;
const int line8 = 7;

enum suitType {SPADES, HEARTS, CLUBS, DIAMONDS};

class cardCls {						//	Define Card as entity with Face Value and Suit
public:
	int value;
	suitType suit;

	string getInt() {				//	Return Face Value on Card (rather than win math)
		switch (value) {
		case 0: return "2"; break;
		case 1: return "3"; break;
		case 2: return "4"; break;
		case 3: return "5"; break;
		case 4: return "6"; break;
		case 5: return "7"; break;
		case 6: return "8"; break;
		case 7: return "9"; break;
		case 8: return "10"; break;
		case 9: return "J"; break;
		case 10: return "Q"; break;
		case 11: return "K"; break;
		case 12: return "A"; break;
		default: return "Unknown getInt(FaceValue) Error"; break;
		}
	}

	string getUpInt() {				//	Return Upside-Down version of Face Value on Card
		switch (value) {
		case 0: return UpTWO; break;
		case 1: return UpTHREE; break;
		case 2: return UpFOUR; break;
		case 3: return UpFIVE; break;
		case 4: return UpSIX; break;
		case 5: return UpSEVEN; break;
		case 6: return UpEIGHT; break;
		case 7: return UpNINE; break;
		case 8: return UpTEN; break;
		case 9: return UpJACK; break;
		case 10: return UpQueen; break;
		case 11: return UpKING; break;
		case 12: return UpACE; break;
		default: return "Unknown getInt(UpsideDownFaceValue) Error"; break;
		}
	}

	string getFace(int line) {		//	Return card's face design by line called
		switch (value) {
		case 12:					//	A, K, Q, & J all show the large suit design
		case 11:
		case 10:
		case 9:
			switch (suit) {
			case SPADES: return AceSPADE[line]; break;
			case HEARTS: return AceHEART[line]; break;
			case CLUBS: return AceCLUB[line]; break;
			case DIAMONDS: return AceDIAMOND[line]; break;
			default: return "         "; break;
			} break;
		case 8:						//	Tens design
			switch (line) {
			case 0:
			case 2:
			case 4:
			case 6: return "  " + showSuit() + "   " + showSuit() + "   "; break;
			case 1:
			case 5: return "    " + showSuit() + "     "; break;
			default: return "          "; break;
			} break;
		case 7:						//	Nines design
			switch (line) {
			case 0:
			case 2:
			case 4:
			case 6: return "  " + showSuit() + "   " + showSuit() + "   "; break;
			case 5: return "    " + showSuit() + "     "; break;
			default: return "          "; break;
			} break;
		case 6:						//	Eights design
			switch (line) {
			case 0:
			case 2:
			case 4:
			case 6: return "  " + showSuit() + "   " + showSuit() + "   "; break;
			default: return "          "; break;
			} break;
		case 5:						//	Sevens design
			switch (line) {
			case 0:
			case 4:
			case 6: return "  " + showSuit() + "   " + showSuit() + "   "; break;
			case 2: return "    " + showSuit() + "     "; break;
			default: return "          "; break;
			} break;
		case 4:						//	Sixes design
			switch (line) {
			case 1:
			case 3:
			case 5:return "  " + showSuit() + "   " + showSuit() + "   "; break;
			default: return "          "; break;
			} break;
		case 3:						//	Fives design
			switch (line) {
			case 1:
			case 5: return "  " + showSuit() + "   " + showSuit() + "   "; break;
			case 3: return "    " + showSuit() + "     "; break;
			default: return "          "; break;
			} break;
		case 2:						//	Fours design
			switch (line) {
			case 1:
			case 5: return "  " + showSuit() + "   " + showSuit() + "   "; break;
			default: return "          "; break;
			} break;
		case 1:						//	Threes design
			switch (line) {
			case 1: return "    " + showSuit() + "     "; break;
			case 5: return "  " + showSuit() + "   " + showSuit() + "   "; break;
			default: return "          "; break;
			} break;
		case 0:						//	Twos design
			switch (line) {
			case 1:
			case 5: return "    " + showSuit() + "     "; break;
			default: return "          "; break;
			} break;
		default: return "          "; break;
		}
	}
			
	string showSuit() {				//	Small face design symbols for each suit
		switch (suit) {
		case SPADES: return "^"; break;
		case HEARTS: return "v"; break;
		case CLUBS: return "+"; break;
		case DIAMONDS: return "o"; break;
		default: return " "; break;
		}
	}
};

class playerType {
public:
	vector<cardCls> hand, pot;		//	Battle from hand, replenish from pot.
	string name = "";
	int wins = 0;

	void shufflePot() {
		cardCls hold;
		int change;
		for (int i = 0; i < pot.size(); i++) {
			change = rand() % pot.size();
			hold = pot[i];
			pot[i] = pot[change];
			pot[change] = hold;
		}
	}

	void reup() {					//	Return pot (winnings) to the hand
		shufflePot();				//	After shuffling
		while (!(pot.size() == 0)) {
			hand.push_back(pot.at(0));
			pot.erase(pot.begin());
		}
	}

	void empty() {					//	Remove all contents to prep for next round
		hand.clear();
		pot.clear();
	}

	int size() {					//	Return all cards under player's control
		return hand.size() + pot.size();
	}

	int power() {					//	Return total value (2=0, ..., A=12) of all cards under player's control
		int strength = 0;
		for (int i = 0; i < hand.size(); i++) {
			strength += hand.at(i).value;
		}
		return strength;
	}

	string potStr() {				//	Return string of # of each card (13 characters); none = space, max: 4
		string pott = "";
		int Ac = 0;
		int tw = 0;
		int th = 0;
		int fo = 0;
		int fi = 0;
		int si = 0;
		int se = 0;
		int ei = 0;
		int ni = 0;
		int te = 0;
		int ja = 0;
		int qu = 0;
		int ki = 0;
		for (int i = 0; i < hand.size(); i++) {
			switch (hand.at(i).value) {
			case 0: tw++; break;
			case 1: th++; break;
			case 2: fo++; break;
			case 3: fi++; break;
			case 4: si++; break;
			case 5: se++; break;
			case 6: ei++; break;
			case 7: ni++; break;
			case 8: te++; break;
			case 9: ja++; break;
			case 10: qu++; break;
			case 11: ki++; break;
			case 12: Ac++; break;
			};
		}
		//	Cast as ASCII to place in character array (string)
		pott = (Ac == 0) ? ' ' : static_cast<char>(Ac + 48);
		pott = (tw == 0) ? pott + ' ' : pott + static_cast<char>(tw + 48);
		pott = (th == 0) ? pott + ' ' : pott + static_cast<char>(th + 48);
		pott = (fo == 0) ? pott + ' ' : pott + static_cast<char>(fo + 48);
		pott = (fi == 0) ? pott + ' ' : pott + static_cast<char>(fi + 48);
		pott = (si == 0) ? pott + ' ' : pott + static_cast<char>(si + 48);
		pott = (se == 0) ? pott + ' ' : pott + static_cast<char>(se + 48);
		pott = (ei == 0) ? pott + ' ' : pott + static_cast<char>(ei + 48);
		pott = (ni == 0) ? pott + ' ' : pott + static_cast<char>(ni + 48);
		pott = (te == 0) ? pott + ' ' : pott + static_cast<char>(te + 48);
		pott = (ja == 0) ? pott + ' ' : pott + static_cast<char>(ja + 48);
		pott = (qu == 0) ? pott + ' ' : pott + static_cast<char>(qu + 48);
		pott = (ki == 0) ? pott + ' ' : pott + static_cast<char>(ki + 48);
		return pott;
	}

	void getName() {
		cout << "Who's Playing today? Enter up to 20 characters: ";
		string nom, nom2;
		nom2 = "";
		getline(cin, nom);
		if (nom.length() > 20) {		//	Truncate to 20 characters to properly handle display
			for (int i = 0; i < 20; i++) {
				nom2 += nom.at(i);
			}
			nom = nom2;
		}
		if (nom.length() < 20) {		//	Extend to 20 characters using extra spaces to properly set up display 
			for (int i = nom.length(); i < 20; i++) {
				nom.append(20 - nom.length(), ' ');
			}
		}
		name = nom;
	}
};

class deckCls {
public:
	cardCls cards[52];				//	Single deck, no jokers

	deckCls() {				//	Generate the deck of cards
		for (int j = 0; j < 4; j++) {
			for (int i = 0; i < 13; i++) {
				cards[i + j * 13].suit = static_cast<suitType>(j);
				cards[i + j * 13].value = i;
			}
		}
	}

	void shuffle() {				//	Trade successive cards with random card from further in the deck
		int change;
		cardCls hold;
		for (int i = 0; i < 52; i++) {
			change = rand() % 52;
			hold = cards[i];
			cards[i] = cards[change];
			cards[change] = hold;
		}
	}

	void cut() {					//	Cuts the deck randomly within ±10 cards from middle
		int cutCard = (52 / 2 - 11) + (rand() % 20);
		cardCls cutDeck[52];
		for (int i = cutCard; i < 52; i++) {
			cutDeck[i - cutCard] = cards[i];
		}
		for (int i = 0; i < cutCard; i++) {
			cutDeck[52 - cutCard + i] = cards[i];
		}
		for (int i = 0; i < 52; i++) {
			cards[i] = cutDeck[i];
		}
	}
	
	//	Deal one card at a time
	void deal(playerType& first, playerType& next) {
		int check = 1;
		for (int i = 0; i < 52; i += 2) {
			first.hand.push_back(cards[i]);
			next.hand.push_back(cards[check]);
			check += 2;
		}
	}
};

int play(playerType&, playerType&);
void display(playerType&, playerType&, int, int);
void applyWinnings(playerType&, playerType&, vector<cardCls>&);
char menu();
bool SetWindow(int, int);
string cornerSuit(suitType, int);
string cornerSuit2(suitType, int);

int main() {
	srand(time(NULL));		//	Apparently, always seed Random Once, and always in Main.

	deckCls newDeck;
	playerType player1, playerComp;
	char menuChar;
	int playCount = 0;
	
	player1.getName();
	

	do {
		newDeck.shuffle();
		newDeck.shuffle();
		newDeck.shuffle();
		newDeck.cut();

		//	Alternate first deal, not that it actually matters
		(playCount % 2 == 0) ? newDeck.deal(player1, playerComp) : newDeck.deal(playerComp, player1);

		if (playCount > 0) {		//	Display wins/losses
			cout << endl << "Wins/Losses: " << player1.wins << "/" << playerComp.wins << endl << endl;
		}

		cout << endl << endl
			<< "          The deck has been shuffled thrice and cut." << endl
			<< "          You have been dealt 26 cards." << endl << endl
			<< "          Let the hostilities begin..." << endl << endl;

		system("pause");

		play(player1, playerComp);
		playCount++;

		//	Prepare for new round
		player1.empty();
		playerComp.empty();

		menuChar = ' ';
		menuChar = menu();
	} while (menuChar == 'y' || menuChar == 'Y');

	system("pause");
	return 0;
}

int play(playerType& player1, playerType& playerComp) {
	vector<cardCls> winnings;		//	Hold cache of cards until applied. Usually 2 cards, can be many more after wars.
	int lastchance = 0;				//	Control for war with player having too few cards.
	int player1Hand, playerCompHand;//	Number of cards in each player's possession, beside pot.
	int	numCardsPlayer = 3;			//	Cards laid aside in times of war.
	int numCardsCompy = 3;	

WAR:

	display(player1, playerComp, numCardsPlayer, numCardsCompy);
	system("pause");

	while (player1.hand.size() >= 1 && playerComp.hand.size() >= 1) {	//	Until either player is empty

		if (player1.hand.at(0).value > playerComp.hand.at(0).value) {	//	Condition: Player1 wins hand
			applyWinnings(player1, playerComp, winnings);				//	Put the winnings in Player1's pot.

		} else if (playerComp.hand.at(0).value > player1.hand.at(0).value) {	// Condition: Computer Player wins hand
			applyWinnings(playerComp, player1, winnings);				//	Put the winnings in Compy's pot.

		} else {								//	Condition: Tie. War imminent.

			if (lastchance == 1) {				//	Player1 has no cards.
				goto PLAYERLOSS;
			} else if (lastchance == 2) {		//	Computer Player has no cards.
				goto COMPYLOSS;
			}

			if (player1.hand.size() > 4 && playerComp.hand.size() > 4) {	//	If both players have enough cards,
				for (int i = 0; i < 4; i++) {								//	place three cards from each into
					winnings.push_back(player1.hand.at(0));					//	the winnings pot.
					winnings.push_back(playerComp.hand.at(0));
					player1.hand.erase(player1.hand.begin());
					playerComp.hand.erase(playerComp.hand.begin());
				}															//	Since they both have enough, reset the
				lastchance = 0;												//	"too few" flag.
				goto WAR;
			}

			//	If Player1 has too few cards, place all but one in the winnings pot. 
			if (player1.hand.size() <= 4) {
				numCardsPlayer = 0;
				while (player1.hand.size() > 1) {				//	Last card will be saved for play.
					winnings.push_back(player1.hand.at(0));
					player1.hand.erase(player1.hand.begin());
					numCardsPlayer++;
				}
				player1Hand = winnings.size();
				if (player1.pot.size() == 0) lastchance = 1;	//	No extra cards? Set the "too few" flag against Player1.
				player1.reup();									//	Extra cards? Put them in Player1's hand.
			}

			//	If Computer Player has too few cards, place all but one in the winnings pot.
			if (playerComp.hand.size() <= 4) {
				numCardsCompy = 0;
				while (playerComp.hand.size() > 1) {			//	Last card will be saved for play.
					winnings.push_back(playerComp.hand.at(0));
					playerComp.hand.erase(playerComp.hand.begin());
					numCardsCompy++;
				}
				playerCompHand = winnings.size() - player1.hand.size();
				if (playerComp.pot.size() == 0) lastchance = 2;	//	No extra cards? Set "too few" flag against Compy.
				playerComp.reup();								//	Extra cards? Put them in Computer Player's hand.
			}									//	As infinitesimal as the chance may be, tie goes to the human player.
		}										//	This is the reason for Computer Player's being evaluated last.

		//	If there are cards left for both players, play on.
		if (player1.hand.size() > 0 && playerComp.hand.size() > 0) {
			display(player1, playerComp, numCardsPlayer, numCardsCompy);
			system("pause");
			numCardsCompy = 3;
			numCardsPlayer = 3;
		}
	}

	//	Apply each player's pot to his hand.
	if (player1.hand.size() == 0 && player1.pot.size() != 0) player1.reup();
	if (playerComp.hand.size() == 0 && playerComp.pot.size() != 0) playerComp.reup();
	
	if (player1.hand.size() == 0) {			//	Player1 ran out of cards on a normal round.
PLAYERLOSS:
		cout << "You have lost against the Computer Player." << endl;
		playerComp.wins++;
		return 0;
	}
	if (playerComp.hand.size() == 0) {		//	Computer Player ran out of cards on a normal round.
COMPYLOSS:
		cout << "YOU HAVE WON!" << endl;
		player1.wins++;
		return 0;
	}
	lastchance = 0;							//	Reset "too few" flag for next game.
	goto WAR;
}

void display(playerType& player1, playerType& playerComp, int numCards, int numCards2) {

	SMALL_RECT windowSize = { 0, 0, 62, 37 };
	system("cls");

	cout << "/////////////////////////////WAR////////////////////////////////" << endl
		<< "/ " << setw(20) << left << player1.name << "                        Computer Player  /" << endl
		<< "/                                                  Power  " << setw(3) << right << playerComp.power() << "  /" << endl
		<< "/ Reserve    " << setw(2) << right << player1.pot.size() << "                                  Reserve   " << setw(2) << right << playerComp.pot.size() << "  /" << endl
		<< "/ AKQJX98765432                                                /" << endl
		<< "/ " << player1.potStr() << "                                                /" << endl
		<< "/                                                              /" << endl
		<< "/                 ----------        ----------                 /" << endl
		<< "/ HAND " << setw(2) << right << player1.hand.size() << "        |" << setw(2) << left << player1.hand.at(0).getInt() << "     " << cornerSuit(player1.hand.at(0).suit, line1) << "|      |" << setw(2) << left << playerComp.hand.at(0).getInt() << "     " << cornerSuit(playerComp.hand.at(0).suit, line1) << "|        " << setw(2) << right << playerComp.hand.size() << " HAND /" << endl
		<< "/                |       " << cornerSuit(player1.hand.at(0).suit, line2) << "|      |       " << cornerSuit(playerComp.hand.at(0).suit, line2) << "|                /" << endl
		<< "/                |" << player1.hand.at(0).getFace(line1) << "|      |" << playerComp.hand.at(0).getFace(line1) << "|                /" << endl
		<< "/                |" << player1.hand.at(0).getFace(line2) << "|      |" << playerComp.hand.at(0).getFace(line2) << "|                /" << endl
		<< "/                |" << player1.hand.at(0).getFace(line3) << "|      |" << playerComp.hand.at(0).getFace(line3) << "|                /" << endl
		<< "/                |" << player1.hand.at(0).getFace(line4) << "|      |" << playerComp.hand.at(0).getFace(line4) << "|                /" << endl
		<< "/                |" << player1.hand.at(0).getFace(line5) << "|      |" << playerComp.hand.at(0).getFace(line5) << "|                /" << endl
		<< "/                |" << player1.hand.at(0).getFace(line6) << "|      |" << playerComp.hand.at(0).getFace(line6) << "|                /" << endl
		<< "/                |" << player1.hand.at(0).getFace(line7) << "|      |" << playerComp.hand.at(0).getFace(line7) << "|                /" << endl
		<< "/                |" << cornerSuit2(player1.hand.at(0).suit, line1) << "       |      |" << cornerSuit2(playerComp.hand.at(0).suit, line1) << "       |                /" << endl
		<< "/                |" << cornerSuit2(player1.hand.at(0).suit, line2) << "     " << setw(2) << right << player1.hand.at(0).getUpInt() << "|      |" << cornerSuit2(playerComp.hand.at(0).suit, line2) << "     " << setw(2) << right << playerComp.hand.at(0).getUpInt() << "|                /" << endl
		<< "/                 ----------        ----------                 /" << endl
		<< "////////////////////////////////////////////////////////////////" << endl;

	string plural = (numCards == 1) ? ". " : "s.";

	if (player1.hand.at(0).value == playerComp.hand.at(0).value) {
		cout << "/                       WAAAAARRRR!!!                          /" << endl
			<< "/                                                              /" << endl
			<< "/                   You have laid aside " << numCards << " card" << plural << "               /" << endl
			<< "/             The Computer Player has laid aside " << numCards2 << ".            /" << endl
			<< "////////////////////////////////////////////////////////////////" << endl << endl;
	}
   	else {
		cout << "/                                                              /" << endl
			<< "/                                                              /" << endl
			<< "/                                                              /" << endl
			<< "/                                                              /" << endl
			<< "////////////////////////////////////////////////////////////////" << endl << endl;
	}
}

void applyWinnings(playerType& winner, playerType& loser, vector<cardCls>& winnings) {
	winner.pot.push_back(loser.hand.at(0));
	winner.pot.push_back(winner.hand.at(0));

	winner.hand.erase(winner.hand.begin());
	loser.hand.erase(loser.hand.begin());

	while (!(winnings.empty())) {
		winner.pot.push_back(winnings.at(0));
		winnings.erase(winnings.begin());
	}
}

char menu() {
	char again;
	cout << "Play again? y/n: ";
	cin.get(again);
	cin.ignore(256, '\n');
	cin.clear();
	return again;
}

//Dharmesh; 03-23-2005//https://www.3dbuzz.com/forum/threads/102195-How-do-you-resize-a-console-window-in-C
bool SetWindow(int Width, int Height)
{
	_COORD coord;
	coord.X = Width;
	coord.Y = Height;

	_SMALL_RECT Rect;
	Rect.Top = 0;
	Rect.Left = 0;
	Rect.Bottom = Height - 1;
	Rect.Right = Width - 1;

	// Get handle of the standard output 
	HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);
	if (Handle == NULL)
	{
		cout << "Failure in getting the handle\n" << GetLastError();
		return FALSE;
	}

	// Set screen buffer size to that specified in coord 
	if (!SetConsoleScreenBufferSize(Handle, coord))
	{
		cout << "Failure in setting buffer size\n" << GetLastError();
		return FALSE;
	}

	// Set the window size to that specified in Rect 
	if (!SetConsoleWindowInfo(Handle, TRUE, &Rect))
	{
		cout << "Failure in setting window size\n" << GetLastError();
		return FALSE;
	}

	return TRUE;
}

string cornerSuit(suitType suit, int line) {
	switch (suit) {
	case SPADES: return CornerSPADE[line]; break;
	case HEARTS: return CornerHEART[line]; break;
	case CLUBS: return CornerCLUB[line]; break;
	case DIAMONDS: return CornerDIAMOND[line]; break;
	default: return "   ";
	}
}

string cornerSuit2(suitType suit, int line) {
	switch (suit) {
	case SPADES: return CornerSPADE2[line]; break;
	case HEARTS: return CornerHEART2[line]; break;
	case CLUBS: return CornerCLUB2[line]; break;
	case DIAMONDS: return CornerDIAMOND2[line]; break;
	default: return "   ";
	}
}