#ifndef _FACEUPPILE_H
#define _FACEUPPILE_H

#include "Pile.h"

class FaceUpPile: public Pile {

 public:
 FaceUpPile(): Pile() { } //constructor (not imherited), explicitly call base constor
  void display() const; //written for us
};

#endif
