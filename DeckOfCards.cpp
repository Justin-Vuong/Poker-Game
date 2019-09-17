#include "DeckOfCards.h"
#include <cstdlib>
#include <iostream>


int DeckOfCards::sizeOfDeck = 52;

DeckOfCards::DeckOfCards(){
   
   deck = new Card[52];
 int index = 0;
 
//Initializing a deck of Card objects
 for(int faceVal = 0; faceVal < 13; faceVal++){
   for(int suitVal = 0; suitVal < 4; suitVal++){
   deck[index].setFace(faceVal);
   deck[index].setSuit(suitVal);
   index++;
  }
 }
 this -> currentCard = 0;
}

Card DeckOfCards::getNumCard(int index){
  return this-> deck[index];
}

int DeckOfCards::getCurrentCard(){
  return this->currentCard;
}

void DeckOfCards::setCurrentCard(int setVal){
  currentCard = setVal;
}

DeckOfCards::~DeckOfCards(){
  delete[] deck;
}

void DeckOfCards::shuffleDeck(){
  srand (time(NULL));
  int swap = 0;
  Card tempCard;
  int swapIndex = 0;
  for(int shuffle = 0; shuffle < 500; shuffle++){
  
  swap = rand() % 52;
  tempCard = this-> deck[swapIndex];

  this-> deck[swapIndex] = deck[swap];
  
  this->deck[swap] = tempCard;
  swapIndex++;
  if(swapIndex == 52)  
    swapIndex = 0;    
  }
}

Card DeckOfCards:: dealCard(){
  if(moreCards() == true){
  this->currentCard += 1;
  return deck[this->currentCard-1];
  } else {
    shuffleDeck();
    this->currentCard = 0;
    return deck[this->currentCard];
  }
}

bool DeckOfCards::moreCards(){
  if(this->currentCard < 52){
    return true;
  } else {
    return false;
  }
}