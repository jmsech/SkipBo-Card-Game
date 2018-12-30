#ifndef _HAND_H
#define _HAND_H

#include "Pile.h"

class Hand: public Pile {
 private:
  const int MAXSIZE = 5; 
 public:
 Hand(): Pile() { }
  bool addCard(const Card& c);
  Card drawCard(const int i);
  void display() const;
  void eraseCard(int i);
};

#endif
