#ifndef _BUILDPILE_H
#define _BUILDPILE_H

#include "FaceUpPile.h"

class BuildPile: public FaceUpPile {
  
 public:
 BuildPile(): FaceUpPile() { }
  // need addCard() to only work if cards in order; clear when full
  bool addCard(const Card& c);

  Card getCard();

};

#endif
