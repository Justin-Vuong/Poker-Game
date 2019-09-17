#include "Dealer.h"
#include "Card.h"
#include <cstdlib>
#include <iostream>
#include <algorithm>

Dealer::Dealer(int playersGame){
  this -> playersInGame = playersGame;
  
  dealerDeck.shuffleDeck();
  
//Initialize array of players (cards in the same row are belong to one player where the number of rows equals to the number of players in the game)
  Card initHand[playersGame][5];
  int indexTemp = 0;
  
  this-> hands = new Card*[playersGame];
  for(int f = 0; f < playersGame; f++)
    this-> hands[f] = new Card[5];

}

Hand Dealer::scoreHand(int playerNum){
  
  int handScore= 0;
  
  //sort out the repeating face cards
  int faceOfCards[5] = {this->hands[playerNum][0].getFace(), this->hands[playerNum][1].getFace(), this->hands[playerNum][2].getFace(), this->hands[playerNum][3].getFace(), this->hands[playerNum][4].getFace()};
  int suitOfCards[5] = {this->hands[playerNum][0].getSuit(), this->hands[playerNum][1].getSuit(), this->hands[playerNum][2].getSuit(), this->hands[playerNum][3].getSuit(), this->hands[playerNum][4].getSuit()};
  int sameSuit = suitOfCards[0];
  
  bool isStraight = true;

/*
This is used for texting hands, you can use it to override the hands of different players if needed
  if (playerNum == 1){
    suitOfCards[0] = 1;
    suitOfCards[1] = 1;
    suitOfCards[2] = 1;
    suitOfCards[3] = 1;
    suitOfCards[4] = 0;
    sameSuit = suitOfCards[0];
  
    faceOfCards[0] = 8;
    faceOfCards[1] = 10;
    faceOfCards[2] = 9;
    faceOfCards[3] = 11;
    faceOfCards[4] = 7;
  } else if (playerNum == 0){
    suitOfCards[0] = 1;
    suitOfCards[1] = 1;
    suitOfCards[2] = 1;
    suitOfCards[3] = 1;
    suitOfCards[4] = 1;
  sameSuit = suitOfCards[0];
  
  faceOfCards[0] = 8;
  faceOfCards[1] = 10;
  faceOfCards[2] = 9;
  faceOfCards[3] = 11;
  faceOfCards[4] = 7;
  } else {
    suitOfCards[0] = 1;
    suitOfCards[1] = 1;
    suitOfCards[2] = 1;
    suitOfCards[3] = 1;
    suitOfCards[4] = 1;
    sameSuit = suitOfCards[0];
  
    faceOfCards[0] = 8;
    faceOfCards[1] = 10;
    faceOfCards[2] = 9;
    faceOfCards[3] = 11;
    faceOfCards[4] = 7;
  }
  */
  std::sort(faceOfCards, faceOfCards+5);
  int single[5] = {-1,-1,-1,-1,-1}; //When there are singles in a hand, their face is stored here (note that the max number of singles you can have in one hand is 5)
  int pair[2] = {-1,-1}; //When there pairs in a hand, their face is stored here (note that the max number of pairs you can have in a hand is 2)
  int threeKind = -1; // Same idea, the face of the 3 of a kind is stored here
  int fourKind = -1; // The face of the 4 of a kind is stored here
  int numSingle = 0; //To make sure that there are no references to non-existing faces, this ensures that only the indexes in singles that have faces are refered to. (Although there are 5 indexes, there arent always 5 singles in a hand)
  int numDouble = 0; //Same idea as numSingles but for the pairs
  
//Placing the values in the arrays single and pair (Ensuring that for repeated face values in the hand that they are only added once to the array)
  int lastCard = faceOfCards[0];
  int streak = 1; 
  for (int s = 1; s < 5; s++){
    if (faceOfCards[s] == lastCard){
      streak++;
    }
    
    if (faceOfCards[s] != lastCard || (faceOfCards[s] == lastCard && s == 4)){ 
      if (streak == 1 && single[0] == -1){
        single[0] = lastCard;
        numSingle++;
      } else if (streak == 1 && single[1] == -1){
        single[1] = lastCard;
        numSingle++;
      } else if (streak == 1 && single[2] == -1){
        single[2] = lastCard;
        numSingle++;  
      } else if (streak == 1 && single[3] == -1){
        single[3] = lastCard;  
        numSingle++;
      } else if (streak == 1 && single[4] == -1){
        single[4] = lastCard;  
        numSingle++;
      } else if(streak == 2 && pair[0] == -1){
        pair[0] = lastCard;
        numDouble++;
      } else if (streak == 2 && pair[1] == -1){
        pair[1] = lastCard;
        numDouble++;
      } else if (streak == 3){
        threeKind = lastCard;
      }   else if (streak == 4){
        fourKind = lastCard;
      }
    }
    
    if (faceOfCards[s] != lastCard && s == 4) {
      if (single[0] == -1){
        single[0] = faceOfCards[s];
        numSingle++;
      } else if (single[1] == -1){
          single[1] = faceOfCards[s];
          numSingle++;
      } else if (single[2] == -1){
          single[2] = faceOfCards[s];
          numSingle++;
      } else if (single[3] == -1){
          single[3] = faceOfCards[s];
          numSingle++;
      } else if (single[4] == -1){
          single[4] = faceOfCards[s];
          numSingle++;
      }
    }
    
    if (faceOfCards[s] != lastCard){
      lastCard = faceOfCards[s];
      streak = 1;
    }
  }
  
  //Now check to see if all the suits of cards are the same
  for(int y = 1; y < 5; y++){
    if (suitOfCards[y] != suitOfCards[y-1])
        sameSuit = -1;
  }
  
  //Check for straight
  int refVal = 0;
  int checkVals = 5; //The number of comparaisons needed to be made. If the lowest number is 2, then an ace can complete a straight which means that only 3 comparaisons need to be made.
  
  if (faceOfCards[0] == 0 && faceOfCards[4] == 12){ // If the straight uses ace as 1
    checkVals = 4;
  } 
  
    refVal = faceOfCards[0];
    for(int g = 1; g < checkVals; g++){
      if(faceOfCards[g] == refVal + 1){
        refVal += 1;
      } else {
        isStraight = false;
      }
    }

//How with all the information, the player's hand can be identified
  int handRanked = 0;
  if(sameSuit > -1 && isStraight == true && single[3] == 11){ //royal flush
    handRanked = 9;
  } else if (sameSuit > -1 && isStraight == true){ //straight flush
    handRanked = 8;
  } else if (fourKind != -1){ //4 of a kind
    handRanked = 7;
  } else if (pair[0] != -1 && threeKind != -1){ //full house
    handRanked = 6;
  } else if (sameSuit > -1){ //flush
    handRanked = 5;
  } else if(isStraight == true){ //Straight
    handRanked = 4;
  } else if (threeKind != -1){ // 3 of a kind
    handRanked = 3;
  } else if (pair[1] != -1){ //since pair[1] can not have a value != -1 unless pair[0] does, this would detect a 2 pair
    handRanked = 2;
  } else if (pair[0] != -1){ //pair
    handRanked = 1;
  } else { //highcard
    handRanked = 0;
  }
  
  Hand handScored(handRanked, single, numSingle, pair, numDouble, threeKind, fourKind, sameSuit);
  return handScored;
}

string Dealer::whoWins(){

  string winner = "0"; //The indexes of the players (Player 1 has index 0, player 2 has index 1 etc.) are stored here. Since it is possible for multiple winners, it is important to use a string here
  
  for(int f = 1; f < playersInGame; f++){
    
//All hands have a rank which corresponds to the type of hand they formed (full house, 2 pair etc). The rest of this method will determine what player(s) have the highest hand which is stored in the string "winner"

    if (playerFinalHand[f].getRank() > playerFinalHand[std::stoi(winner.substr(0,1))].getRank()){ //If the rank is higher than you automatically know that a player has a higher hand than the current placeholder for the highest hand. This loop will iterate through all the players to see who has the highest hand
      winner = to_string(f);
    } else if ((playerFinalHand[f].getRank() == playerFinalHand[std::stoi(winner.substr(0,1))].getRank())){ //If 2 players have the same rank of hand, then you must go into the details and determine which one is higher or if they tie
    
      if(playerFinalHand[f].getRank() == 9){//royal flush
          winner += to_string(f);
      } else if (playerFinalHand[f].getRank() == 8){ //straight flush
        if(playerFinalHand[f].getSingles(4) > playerFinalHand[std::stoi(winner.substr(0,1))].getSingles(4)){
          winner = to_string(f);
        } else if (playerFinalHand[f].getSingles(4) == playerFinalHand[std::stoi(winner.substr(0,1))].getSingles(4)){
          winner +=  to_string(f);
        }
      } else if (playerFinalHand[f].getRank() == 7){ //four of a kind
        if(playerFinalHand[f].getFourKind() > playerFinalHand[std::stoi(winner.substr(0,1))].getFourKind()){
          winner = to_string(f);
        }
      } else if (playerFinalHand[f].getRank() == 6){ //full house
        if(playerFinalHand[f].getThreeKind() > playerFinalHand[std::stoi(winner.substr(0,1))].getThreeKind()){
          winner = to_string(f);
        }
      } else if (playerFinalHand[f].getRank() == 5){ //flush
        int decide = 1; //if the currently largest hand is still the largest, it will set decide to 2, if the new hand is larger then it will replace it and decide will be set to 0
        for(int c = 4; c >= 0; c--){
          if(playerFinalHand[f].getSingles(c) == playerFinalHand[std::stoi(winner.substr(0,1))].getSingles(c) && decide == 1){ //need to check the next highest value
            if (c == 0){
              winner += to_string(f);
            }
          } else if (playerFinalHand[f].getSingles(c) > playerFinalHand[std::stoi(winner.substr(0,1))].getSingles(c) && decide == 1){
            decide = 0;
            winner = to_string(f);
          } else if (playerFinalHand[f].getSingles(c) > playerFinalHand[std::stoi(winner.substr(0,1))].getSingles(c) && decide == 1){ //The hand is lower, keep the current highest cards
            decide = 2;
          }
        }
      } else if (playerFinalHand[f].getRank() == 4){ //straight
        if(playerFinalHand[f].getSingles(0) > playerFinalHand[std::stoi(winner.substr(0,1))].getSingles(0)){
          winner = to_string(f);
        } else if (playerFinalHand[f].getSingles(0) == playerFinalHand[std::stoi(winner.substr(0,1))].getSingles(0)){
          winner += to_string(f);
        } //if none of these pass, then the current highest is still the highest so no need to change the string
      } else if (playerFinalHand[f].getRank() == 3){ //3 of a kind
        if(playerFinalHand[f].getThreeKind() > playerFinalHand[std::stoi(winner.substr(0,1))].getThreeKind()){
            winner = to_string(f);
        } //can not tie with 3 of a kind so this is the only statement needed, if this is not true then the current highest hand is still the highest
    } else if (playerFinalHand[f].getRank() == 2){
        if(playerFinalHand[f].getDoubles(1) > playerFinalHand[std::stoi(winner.substr(0,1))].getDoubles(1)){
          winner = to_string(f);
        } else if (playerFinalHand[f].getDoubles(1) == playerFinalHand[std::stoi(winner.substr(0,1))].getDoubles(1)){
          if(playerFinalHand[f].getDoubles(0) > playerFinalHand[std::stoi(winner.substr(0,1))].getDoubles(0)) {
            winner = to_string(f);
          } else if (playerFinalHand[f].getDoubles(0) == playerFinalHand[std::stoi(winner.substr(0,1))].getDoubles(0)){
            winner += to_string(f);
          }
        }
    } else if (playerFinalHand[f].getRank() == 1) { //pair
      if(playerFinalHand[f].getDoubles(0) > playerFinalHand[std::stoi(winner.substr(0,1))].getDoubles(0)) {
            winner = to_string(f);
      } else if (playerFinalHand[f].getDoubles(0) == playerFinalHand[std::stoi(winner.substr(0,1))].getDoubles(0)){
        if(playerFinalHand[f].getSingles(2) == playerFinalHand[std::stoi(winner.substr(0,1))].getSingles(2)){
          int check = 0;
          
          for(int g = 1; g >=0; g--){
            if(playerFinalHand[f].getSingles(g) > playerFinalHand[std::stoi(winner.substr(0,1))].getSingles(g) && check == 0){
              check =1;
              winner = to_string(f);
            } else if(playerFinalHand[f].getSingles(g) < playerFinalHand[std::stoi(winner.substr(0,1))].getSingles(g) && check == 0){
              check = 1;
            } else if (g == 0){
              winner += to_string(f);
            }  
          }
        } else if (playerFinalHand[f].getSingles(2) > playerFinalHand[std::stoi(winner.substr(0,1))].getSingles(2)){
          winner = to_string(f);
        }
      }
    } else if (playerFinalHand[f].getRank() == 0){ //singles
      int checker = 0; 
      for(int g = 4; g >=0; g--){
            if(playerFinalHand[f].getSingles(g) > playerFinalHand[std::stoi(winner.substr(0,1))].getSingles(g) && checker == 0){
              checker =1;
              winner = to_string(f);
            } else if(playerFinalHand[f].getSingles(g) < playerFinalHand[std::stoi(winner.substr(0,1))].getSingles(g) && checker == 0){
              checker = 1;
            } else if (g == 0){
              winner += to_string(f);
            }  
          }
    } 
  }
}

 return winner; 
}

Card Dealer::getCard(int playerNum, int cardNum){
  return this-> hands[playerNum][cardNum];
}

void Dealer::switchCard(int playerNum, int numCardInHand){
  this -> hands[playerNum][numCardInHand] = this -> dealerDeck.dealCard();
}

void Dealer::startNewHand(){
  
  dealerDeck.setCurrentCard(0);
  dealerDeck.shuffleDeck();

//dealing Cards to players
  for(int x = 0; x < 5;x++){
    for(int a = 0; a < playersInGame; a++){
      hands[a][x] = dealerDeck.dealCard();
    }
  }
  
}

int Dealer::getPlayersInGame(){
  return playersInGame;
}

Hand Dealer:: getHand(int player){
  return playerFinalHand[player];
}

void Dealer:: setFinalHand(string playersIn){
  
  playerFinalHand = new Hand[getPlayersInGame()];
  
  for(int y = 0; y < getPlayersInGame(); y ++){
    playerFinalHand[y] = scoreHand(stoi(playersIn.substr(y,1)));
  }
  
}