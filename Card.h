#include <string>

using namespace std;

#ifndef CARD_H
#define CARD_H

class Card {
  private: 
    int face;
    int suit;
  
  public:
    Card();
    static string nameSuits[];
    static string nameFace[];
    static string convertFaceName(int);
    static string convertSuitName(int);
    string toString();
    int getFace();
    int getSuit();
    void setFace(int);
    void setSuit(int);
    Card(int, int);
    Card(const Card &obj);
  
};

#endif