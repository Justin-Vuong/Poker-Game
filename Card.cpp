#include "Card.h"
#include <cstdlib>
#include <iostream>

string Card::nameSuits[4] = {"Diamonds", "Clubs", "Hearts", "Spades"};

string Card::nameFace[13] = {"Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King", "Ace"};
  
Card::Card(){
  suit = 0;
  face = 2;
}

string Card::convertFaceName(int value){
  return nameFace[value];
}

string Card::convertSuitName(int value){
  return nameSuits[value];
}

string Card::toString(){
  string output = nameFace[face] + " of " + nameSuits[suit];
  return output;
}

int Card::getFace(){
  return this -> face;
}

int Card::getSuit(){
  return this -> suit;
}

void Card::setFace(int input){
  this->face = input;
}

void Card::setSuit(int input){
  this-> suit = input;
}

Card::Card(int faceVal, int suitVal){
  this->face = faceVal;
  this->suit = suitVal;
}

Card::Card(const Card &obj) {
   face = obj.face; // copy the value
   suit = obj.suit;
}
