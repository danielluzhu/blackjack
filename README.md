# blackjack

readme.txt

Name: blackjack.cpp

To Compile (on Mac OSX):
	g++ -std=c++11 -stdlib=libc++ blackjack.cpp -o blackjack

Files:
	- blackjack.cpp

Description: 
	1 User can play blackjack with 1 computer player. Further requirements are listed below. 

Instructions: 
	Please implement a command-line blackjack game using C, C++, or Objective-C:

	Requirements

	•   Dealer must hit on soft 17
	•   Single Deck. The deck is shuffled every 6 rounds. 
	•   Player is not allowed to split cards. 
	•   Keep track of win percentage for the player.
	•   Provide a readme file explaining how to compile the source and other info that might be interesting.

	You don't have to implement any AI other than the one mentioned above - it's just one player vs. dealer.

	If any third party code is used, please give credit and cite source.

Game Rules: 
	- Players start with 2 card each.
	- The first card dealt to every player is visible to the field.
	- Players can either "Hit" or "Stand"
		- Hit: Add a card to a player's hand.
		- Stand: Pass on turn.
	- Once a player's hand totals to above 21, they automatically lose the round.
	- Every numerical card is equal its numerical value.
	- Jack, Queens, and Kings are equal to 10.
	- Aces can be either 1 or 11.
	- User is dealed card first. 
	- User plays first in any round. 
	- When all players stand, highest total (that is <= 21) wins the round.
	- Dealer wins in ties.
	- Every round starts with new cards. 

Computer Player Notes:
	- If the hand's total is < 17, computer will hit
		- Soft 17: when the hand totals to 17 when an "Ace" card is used to equal "11"
			ex/ Soft 17 Hand: Ace 6
			ex/ Hard 17 Hand: 10  7
	- If the hand's total is a hard 17 or is > 18, computer will stand

Future Changes: 
	Game: 
	- Split rules
		- To be honest, I don't really know what this means
	- Betting option 



	- Implement a Hand class 
		- Better organize code (showField), handContents(), getTotal(), maxHand)
		- Make the game more scalable with more players
	- Implement a Deck class
		- Better organize deck code (deck(), shuffle(), deckPoint)
	- Implement a Card class
		- Card would replace ints and could be better graphically represented 
		- Could also be used in other card games
	- Multiple players
		- Multiple humans
		- Multiple computers 
