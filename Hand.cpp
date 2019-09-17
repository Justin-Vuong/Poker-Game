#include "Hand.h"
#include <cstdlib>


Hand::Hand(int cardsRank, int* singleFaces, int numberSingles, int* doubleFaces, int numberDoubles, int threeOfKind, int fourOfKind, int cardsSuit){
  this -> rank = cardsRank;
  this -> numSingle = numberSingles;
  this -> numDouble = numberDoubles;
  this -> threeKind = threeOfKind;
  this -> fourKind = fourOfKind;
  this -> suit = cardsSuit;
  
  //prevent having unused indexes (the ones set to -1)
  this -> singles = new int[numberSingles];
  for(int q = 0; q < numberSingles;q++)
    this -> singles[q] = singleFaces[q];
  
  this -> doubles = new int[numberDoubles];
  for(int p = 0; p < numberDoubles; p++)
    this -> doubles[p] = doubleFaces[p];

}
Hand::Hand(){
  this -> rank = 0;
  this -> numSingle = 5;
  this -> numDouble = 1;
  this -> threeKind = 0;
  this -> fourKind = 0;
  this -> suit = 0;
  

  this -> singles = new int[5];
  singles[0] = 1;
  singles[1] = 2;
  singles[2] = 3;
  singles[3] = 4;
  singles[4] = 5;
  
  this -> doubles = new int[5];
  doubles[0] = 1;
  doubles[1] = 2;
  doubles[2] = 3;
  doubles[3] = 4;
  doubles[4] = 5;
} 

int Hand::getNumSingle(){
  return this -> numSingle;
}

int Hand::getNumDouble(){
  return this -> numDouble;
}

int Hand::getSingles(int index){
  return this -> singles[index];
}

int Hand::getDoubles(int index){
  return this -> doubles[index];
}

int Hand::getRank(){
  return this -> rank;
}

std::string Hand::toString(){
  std::string outputName = "";
  
  if (this-> rank == 0){
    outputName = Card::convertFaceName(this->singles[this->numSingle -1]) + " High Card";
  } else if (this-> rank == 1){
    outputName = "Pair of " + Card::convertFaceName(this->doubles[this->numDouble -1]) + "'s";
  } else if (this-> rank == 2){
    outputName = "Two Pair " + Card::convertFaceName(this->doubles[this->numDouble-1]) + "'s";
  } else if (this-> rank == 3){
    outputName = "Three " + Card::convertFaceName(this->threeKind) + "'s" ;
  } else if (this-> rank == 4 && singles[0] == 0){ //If ace is used for a 1
    outputName = "5 High Straight";
  } else if (this-> rank == 4){
    outputName = Card::convertFaceName(this->singles[this->numSingle -1]) + " High Straight";
  } else if (this-> rank == 5){
    outputName = Card::convertFaceName(this->singles[this->numSingle -1]) + " High Flush of " + Card::convertSuitName(this -> suit);
  } else if(this-> rank == 6){
    outputName = "Full House " + Card::convertFaceName(threeKind) + "'s";
  } else if (this -> rank == 7){
    outputName = "Four " + Card::convertFaceName(fourKind) + "'s";
  } else if (this -> rank == 8 && singles[0] == 0){
    outputName = "5 High Straight Flush of " + Card::convertSuitName(this -> suit); 
  } else if (this -> rank == 8){
    outputName = Card::convertFaceName(this->singles[this->numSingle -1]) + " High Straight Flush of " + Card::convertSuitName(this -> suit);
  } else {
    outputName = Card::convertSuitName(this -> suit) + " Royal Flush";
  }

  return outputName;
  
}

int Hand::getThreeKind(){
  return this -> threeKind;
}

int Hand::getFourKind(){
  return this -> fourKind;
}