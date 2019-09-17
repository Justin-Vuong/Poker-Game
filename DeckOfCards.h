#include <string>
#include "Card.h"
#include "Hand.h"

using namespace std;

#ifndef DECKOFCARDS_H
#define DECKOFCARDS_H

class DeckOfCards {
  private: 
    int currentCard;
    Card *deck;
  
  public:
    DeckOfCards();
    Card getNumCard(int);
    int getCurrentCard();
    void setCurrentCard(int);
    static int sizeOfDeck;
    ~DeckOfCards();
    void shuffleDeck();
    Card dealCard();
    bool moreCards();
};

#endif