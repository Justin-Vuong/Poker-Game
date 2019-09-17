#include <iostream>
#include <Card.h>
#include <DeckOfCards.h>
#include <Dealer.h>
#include <Hand.h>
#include <cmath>

int main() {
  string remindHands = "The hands from highest to lowest in poker are:\nStraight Flush: A run of five cards in sequence all with the same suit\nFour of a Kind: Four cards of the same face value\nFull House: A set of three and a set of two cards with the different face values\nFlush: Five cards of the same suit\nStraight: Five cards in sequence\nThree of a Kind: Three cards with the same face value\nTwo Pairs: Two sets of two cards that have the same face values\nPair: One set of two cards that have the same face value\nHigh Card: When no player's cards form any hand, the player with the highest card wins.\n\nNote that Aces are high but can still be used as ones in straights. Also, if 2 or more players have the same hand (ie. flush) \nthe winner is decided by the player with the highest face value of the card in the set.\n\n";
		
cout<< "Welcome to a poker simulation game. There are four spots, how many people are playing today? ";
		int numPlayers = 0; //Keeps track of how many players are playing in the game
		
		do { 
			cin >> numPlayers;
			
//Making sure that the user input for the number of players is valid
			if(numPlayers < 0) {
				cout << "You can not have negative players! Enter a non-negative integer: ";
			} else if(numPlayers > 4){
			  cout << "The maximum number of players you can have is 4. Please enter an integer between 1-4 players inclusive: ";
			}
			
		} while (numPlayers<0 || numPlayers > 4);
 
 if(numPlayers == 0) {
			cout << "No one to play, what a shame.";
			return 0;
		} else if (numPlayers == 1) {
			cout << "Well it looks like you are gonna have to play against yourself. \nIm adding another player for you so you are not lonely.";
			numPlayers = 2;
			
		}
 
//Starting the hand by creating an instance of the Dealer Class
   Dealer d1(numPlayers);
 
 string playersInGame=""; // This string keeps track of which players to iterate through in a hand. (It is what I had in mind to keep track of the players that have not been eliminated which was not fully implemented)
		int *coins = new int[numPlayers]; //Keep track of which players how how many coins

//Initializing the player's coins
		int highestBet = 49;
		for(int c = 0; c < numPlayers; c++) {
			coins[c] = 500; //Default everyone starts with 500 coins
			playersInGame+= to_string(c); //Every player's index is added to the string playersInGame so that they will have a chance to play the game
		}
		cout << "\nGreat! Now does everyone know how to play poker? (Enter \"n\" for rules or anything else to continue): ";
		
		string answer = "";
		cin >> answer;
		 if (answer == "n") {
			 cout << "\nHere is a quick run down. Poker is a card game where players face off with wages and win rounds by having "
			 		<< "the highest hand. \nPlayers are eliminated if they have nothing left to bet. A hand can be anything from a pair or even "
			 		<< "a single card but these \nare not strong hand and do not give high chances of winning rounds. In this version, you are "
			 		<< "asked to bet before you see your \ncards meaning you do not often want to bet everything you have on one round.\n\n" 
			 		<< "For your reference, t" << remindHands.substr(1, 810);
		 }
		 
//This stores the amount and keeping track of the pot by asking players what they want to bet
		 int pot = 0;
		 highestBet = 49;
			for (int x = 0; x < playersInGame.length(); x++) { 
				if(highestBet == 49){
				  cout << "\nPlayer " << stoi(playersInGame.substr(x,1)) +1 << ", you get first bet. You have " << to_string(coins[stoi(playersInGame.substr(x,1))]) << " coins and the minimum bet is 50 coins.\nHow much would you like to bet? ";
				} else {
				cout << "\nPlayer " << to_string(stoi(playersInGame.substr(x,1))+1) << ", you are up. You have " << to_string(coins[stoi(playersInGame.substr(x,1))]) << " coins.\nHow much would you like to bet? You must match the bet of " << to_string(highestBet) << " coins or go all in: ";	
				}
				
				int bet=0;
				bool validBet = false;
				do {
					//Betting	
					cin >> bet;	
					if(highestBet == 49 && bet > coins[stoi(playersInGame.substr(x,1))]){
					  cout <<"You only have " << coins[stoi(playersInGame.substr(x,1))] << " coins. Enter a bet less than or equal to your balance: ";
					} else if(highestBet == 49 && bet >= 50){
					  validBet = true;
					  highestBet = bet;
					} else if(highestBet == 49 && bet < 50) {
						cout << "Invalid bet. The minimum bet is 50 coins per round. How many coins would you like to bet this round? ";
					}else if (bet < highestBet && bet != coins[stoi(playersInGame.substr(x,1))]) { 
					  cout << "You need to match the " << highestBet << " coin bet or go all in. Enter a bet: ";
					} else if (bet > coins[stoi(playersInGame.substr(x,1))]) {
						cout << "You only have " << coins[stoi(playersInGame.substr(x,1))] << " coins, please enter a bet lower than or equal to your balance: ";
					} else if (bet > highestBet){
					  validBet = true;
					  highestBet = bet;
					} else if (bet == coins[stoi(playersInGame.substr(x,1))]) {
					   validBet = true;
					}else{ //matched exactly the bet
					  validBet = true;
					}
				} while (!validBet);
				int tester = stoi(playersInGame.substr(x,1));
				
				coins[tester] -= bet;
				
				pot += bet;
				//Prepare output


//Now that all the pre game details are sorted, the hand starts here
				d1.startNewHand();

//Output the Cards in the player's hand
				cout << "\nHere is your hand\n";
				for(int s = 1; s < 6; s++) {
					cout << "[" << to_string(s) << "] ";
					cout << d1.getCard(stoi(playersInGame.substr(x,1)),s-1).toString() << "\n";
				}
				
				int numCardsSwitched = 8; //Players get up to 8 chances to switch cards
		
//Looking for input if the player wants to switch their cards
				cout << "\nNow that you have seen your hand, you can switch a card for a new one from the deck. You can do this up to 8 times.\nIf you need a reminder of what the hands are in poker enter \"-1\".\nOtherwise enter the number surrounded by square brackets to switch a card or 0 to keep your current ones: ";
				int switchCards;
				do {
					bool valid;
					do {
					  valid =true;
						cin >> switchCards;
						if (switchCards < -1 || switchCards > 5) {
							cout << "Invaid Input. Please enter a single integer between -1 and 5 inclusive to decide what to do with your hand.";
							valid = false;
						}
					} while (valid == false);
		
					if(switchCards == -1) {//Player asked for instructions
						cout << "\n" << remindHands;	
						cout << "Here is your hand";
						for(int s = 1; s < 6; s++) {
							cout << "["<< s <<"] ";
							cout << d1.getCard(stoi(playersInGame.substr(x,1)),s-1).toString() << "\n";
						}
						cout << "\nEnter the number surrounded by square brackets to switch a card or 0 to keep your current ones: ";
					} else if(switchCards == 0) { //Player wants to hold cards
						numCardsSwitched = 0;
					} else {//Switch Card
					
						string oldCard = d1.getCard(stoi(playersInGame.substr(x,1)),switchCards-1).toString();
						d1.switchCard(stoi(playersInGame.substr(x,1)),switchCards-1);

						numCardsSwitched--;

						if(numCardsSwitched > 0) {
							cout << "\n########################################################################################################" 
								<< "\n\n"<< oldCard << " -----> was switched for -----> " << d1.getCard(stoi(playersInGame.substr(x,1)),switchCards-1).toString() <<  "\nYou can switch up to " 
							 	<< numCardsSwitched << " more times.\n\n------- YOUR HAND ------\n[1] "<< d1.getCard(stoi(playersInGame.substr(x,1)),0).toString() << "\n[2] "<< d1.getCard(stoi(playersInGame.substr(x,1)),1).toString() 
							 	<< "\n[3] "<< d1.getCard(stoi(playersInGame.substr(x,1)),2).toString() <<"\n[4] "<< d1.getCard(stoi(playersInGame.substr(x,1)),3).toString() << "\n[5] "<< d1.getCard(stoi(playersInGame.substr(x,1)),4).toString() << "\n\nEnter the number "
							 	<< "surrounded by square brackets to switch a card or 0 to keep your current ones: ";
						}else {
							cout << "\n" <<"########################################################################################################" 
								<< "\n\n"<<oldCard << " -----> was switched for -----> " << d1.getCard(stoi(playersInGame.substr(x,1)),switchCards-1).toString() << "\n\n------- YOUR HAND "
								<< "------\n[1] "<< d1.getCard(stoi(playersInGame.substr(x,1)),0).toString() << "\n[2] "<< d1.getCard(stoi(playersInGame.substr(x,1)),1).toString() 
							 	<< "\n[3] "<< d1.getCard(stoi(playersInGame.substr(x,1)),2).toString() <<"\n[4] "<< d1.getCard(stoi(playersInGame.substr(x,1)),3).toString() << "\n[5] "<< d1.getCard(stoi(playersInGame.substr(x,1)),4).toString();
						}
					}
				} while (numCardsSwitched  > 0);
       
       
//The player has finalized their hand so it but be analyzed and assigned a score (identify the hand it makes)       
				//Put these pauses so the player can take the time to read what is going on
				cout << "\nYour hand has been recognized as a : " << d1.scoreHand(stoi(playersInGame.substr(x,1))).toString();
				
				cout << "\n\nEnter anything to continue: ";
				string wait;
				cin >> wait;

			}
		
			d1.setFinalHand(playersInGame);
		
//Determining and outputting the winner of the hand			
			int whoWon = 0;
			string winnerOfHand = d1.whoWins();
		
			string whichWinners = "Player " + to_string(stoi(winnerOfHand.substr(0,1)) +1);
		  
			if(winnerOfHand.length() > 1) {//This would happen if there are 2 players that share the same winning hand meaning they tie
				for(int i = 0; i < winnerOfHand.length(); i++) {
					//Split the coins evenly
					coins[stoi(winnerOfHand.substr(i, 1))] += (int) std::floor(pot/winnerOfHand.length());
					if(i>0) {
						whichWinners += ", Player " + to_string((stoi(winnerOfHand.substr(i,i+1)) + 1));
					}
				}
				whoWon = stoi(winnerOfHand.substr(0,1));
			} else {//There is only one winner
				whoWon = stoi(winnerOfHand);
				coins[whoWon] += pot;
			}
				
			cout << "\n########################################################################################################"
					<< "\nThe cards are in! The winner of the " << pot << " coin pot is...\n" << whichWinners << " with a " << d1.getHand(whoWon).toString() << "\n";
					
//Display the rest of the hands after the winner(s) hand is shown
				cout << "\n\nHere were all the hands\n";
				for(int d = 0; d < playersInGame.length(); d++) {
					cout << "Player " << to_string(stoi(playersInGame.substr(d,1))+1) << " had a " << d1.getHand(stoi(playersInGame.substr(d,1))).toString() <<endl;
				}
	
//Print all of the balances of the players that are in
			cout << "\nThe current balances are:\n";
			for(int e = 0; e < playersInGame.length(); e++) {
				cout << "Player " << stoi(playersInGame.substr(e,1))+1 << ": " << coins[stoi(playersInGame.substr(e,1))] << "\n";
			}
			
		cout << "Game Over!";
 
}