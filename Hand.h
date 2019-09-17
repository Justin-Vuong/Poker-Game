#include <string>
#include "Card.h"

#ifndef HAND_H
#define HAND_H

class Hand {
  private: 
    int rank;
    int numSingle;
    int numDouble;
    int* singles;
    int* doubles;
    int threeKind;
    int fourKind;
    int suit;
    
  public:
    Hand(int, int*, int, int*, int, int, int, int);
    Hand();
    int getRank();
    int getNumSingle();
    int getNumDouble();
    int getSingles(int);
    int getDoubles(int);
    int getThreeKind();
    int getFourKind();
    std::string toString();

};

#endif