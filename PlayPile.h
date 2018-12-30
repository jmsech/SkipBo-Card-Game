#ifndef _PLAYPILE_H
#define _PLAYPILE_H

#include "FaceUpPile.h"

class PlayPile: public FaceUpPile {
  
 public: 
 PlayPile(): FaceUpPile() { }
  
  Card drawCard();
  void eraseCard();
};

#endif
