#include <string>
#include "Card.h"
#include "DeckOfCards.h"
#include "Hand.h"

using namespace std;

#ifndef DEALER_H
#define DEALER_H

class Dealer {
  private: 
    DeckOfCards dealerDeck;
    int playersInGame;
    Card** hands;
    Hand* playerFinalHand;
    
  public:
    Dealer(int);
    Hand scoreHand(int);
    string whoWins();
    Card getCard(int,int);
    void switchCard(int, int);
    void startNewHand();
    int getPlayersInGame();
    Hand getHand(int);
    void setFinalHand(string);

};

#endif