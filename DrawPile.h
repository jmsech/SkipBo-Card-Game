#ifndef _DRAWPILE_H
#define _DRAWPILE_H

#include "Pile.h"
#include <iostream>

class DrawPile: public Pile {
 private:
  bool rand;
 public:
 DrawPile(bool rand = true) : Pile(), rand(rand) { }
  //DrawPile(bool rand): Pile(), rand(rand) { }
  friend class SkipBoGame;
  void display() const; 
  bool getRand() const { return rand; }
  void shuffle(); //shuffle the deck for rand = true
  Card drawCard();
  void setRand(bool shuffle);
  void addTop(const Card& c, int i) { pile.insert(pile.begin()+i, c); }
};

#endif
