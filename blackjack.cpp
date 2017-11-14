/* blackjack.cpp
 * Daniel Zhu
 * 
 * In my attempts to impress you. 
 */

#include <stdlib.h> 
#include <iostream>
#include <tuple>
#include <string>

using namespace std;

const int max = 21;			// Max valid value of a hand in blackjack
const int maxHand = 12; 	// Max number of cards in a hand 11: A+A+A+A+2+2+2+2+3+3+3 = 21
const int shuffleDeck = 6;	// Shuffles deck after 6 rounds
const int dealerSoft = 17;	// Value at which the dealer hits if soft

int wins, roundCount;
double winPerc; 			// of the user

int cards[52]= {0};			// deck of cards
int deckPoint; 				// Current index of deck
int standCount; 			// used to signal when both players stand (ending the round)

// These are the hands of the 2 players 
int user[maxHand] = {0}; 	
int dealer[maxHand] = {0};
int uit, dit; 				// index of the card position in the hand

// Calculates the win percent
double winPercent(){
	if (roundCount == 0) {
		return -1;
	}
	return 100.0*wins/roundCount;
}

// gets the next card in the deck, returns -1 if bad index;
int nextCard() {
	if (deckPoint > 51 || deckPoint < 0) {
		return -1; 
	}
	deckPoint++;
	return cards[deckPoint-1];
}

// Player's Action
// Add a card to the specified player's hand
void hit(int hand[], int* handIndex) {
	hand[*handIndex] = nextCard();
	(*handIndex)++;
}

// Player's Action
// No card is added
void stand() {
	standCount++;
}

// Returns the sum and whether or not theres an ace 
// 	The bool is important for determining soft vs hard
tuple<int, bool> getTotal(int hand[], int iter) {
	int sum = 0;
	bool ace = false;
	for (int i = iter - 1; i >= 0; i--) {
		sum = sum + hand[i];
		if (hand[i] == 1) {
			ace = true;
		}
	}
	if (sum < 12 && ace) {
		return std::make_tuple(sum+10, ace); 
	}
	return std::make_tuple(sum, ace); 
}

// Prints a hand's contents 
// 	Used in showField()
void handContents(int hand[], int iter, bool show) {
	for (int i = 0; i < iter; i++) {
		if (show || i == 0) {
			int x = hand[i];
			if (x == 1) {
				cout << "A  ";			
			} else {
				cout << x << " ";
				if (x < 10) {
					cout << " ";
				}			
			}
		} else {
			cout << "*  ";	
		}
	}
	cout<< "\n";
}

// prints out the entire field, showing 1 dealer card and all the user cards
void showField(bool show) {
	cout << "\n Your Hand:     ";
	handContents(user, uit, true);	
	cout << " Dealer's Hand: ";
	handContents(dealer, dit, show);
}

// Shuffles the deck
void shuffle() {
	int newDeck[52] = {0};
	for (int i = 51; i >= 0; i--) {
		int j = rand()%52;
		while (newDeck[j] != 0) {
			j = rand()%52;
		}
		newDeck[j] = cards[i];
	}
	memcpy(cards,newDeck, 52*8);
	deckPoint = 0;
}

// Creates a deck of 52 ints
void deck() {
    deckPoint = 0;
    int val[13] = {1,2,3,4,5,6,7,8,9,10,10,10,10};
    for (int i=51; i>=0; i--) {
    	cards[i] = val[i%13];
    }  
    shuffle();
}

// Sets up the game of Blackjack
void setup() {
	deck();	
	wins = 0;
	roundCount = 0;
	standCount = 0;
	winPerc = 0.0;
	cout << "Playing Blackjack \n";
}

// Starts a new round within the game (players can win/lose a round)
void startNewRound() {
	cout << "\n**************************************** \n";
	roundCount++;
	cout << "Round: " << roundCount << " \n";
	standCount = 0;

	if (roundCount % shuffleDeck == 1) {
		shuffle();
	}
	memset(user, 0, sizeof(user));
	memset(dealer, 0, sizeof(dealer));
	uit = 0;
	dit = 0;
	hit(user, &uit);
	hit(dealer, &dit);
	hit(user, &uit);
	hit(dealer, &dit);
}

// The dealer AI, hits if hand < 17 soft, stands otherwise
void dealerMove() {
	tuple<int,bool> curr = getTotal(dealer, dit);
	if (get<0>(curr) < dealerSoft || 
		(get<0>(curr) == dealerSoft && get<1>(curr))) {
		cout<<"  Dealer hit \n";
		hit(dealer, &dit);
	} else {
		cout<<"  Dealer stand \n";
		stand();
	}
}

// Plays a round of black jack
// Returns true if the user wins, false if the user loses
bool playRound() {
	string resp;
	while(1) {
		bool validInput = false;
		showField(false);
		standCount = 0;
		while (!validInput) {
			cout << "  What you do? (Hit/Stand): ";
			std::getline(cin, resp);
			if (resp.at(0) == 'H' || resp.at(0) == 'h') {
				hit(user, &uit);
				validInput = true;
				if (get<0>(getTotal(user, uit)) > 21) {
					return false;
				} 
			} else if (resp.at(0) == 'S' || resp.at(0) == 's') {
				stand(); 
				validInput = true;
			} else {
				cout << "Invalid Input. Retry. ";
				validInput = false;
			}
		}
		dealerMove();
		if (get<0>(getTotal(dealer, dit)) > 21) {
			return true; 
		}
		if (standCount == 2) {
			return (get<0>(getTotal(user, uit))) > (get<0>(getTotal(dealer, dit)));
		}
	}
}

// Ends a particular round in the blackjack game
void endOfRound(bool win) {
	showField(true);
	if (win) {
		cout << "\n    You Win!!!! \n";
		wins++;
	} else {
		cout << "\n    You lose... \n";
	}
	winPerc = winPercent();
	cout << "\nEnd of Round \n";
	cout << " SCORE:  User: " << get<0>(getTotal(user, uit));
	cout << " Dealer: " << get<0>(getTotal(dealer, dit)) << "\n";
	cout << "         Wins: " << wins << " Rounds: " << roundCount << "\n";
	cout << "         WinP: " << winPerc << "\n";
}

int main() {
	setup();
	bool cont = true;
	while (cont) {
		startNewRound();
		bool win = playRound();
		endOfRound(win);
		cout << "Keep playing? ('N' to exit)\n";
		string resp;
		std::getline(cin, resp);
		if (resp.at(0) == 'N' || resp.at(0) == 'n') {
			cont = false; 
		}
	}
}