#include <iostream>
#include <algorithm>
#include <random>
#include "DrawPile.h"

// for live game play - must not change!
void DrawPile::display() const {
  std::cout << "[XX]/" << size();
}

void DrawPile::shuffle() {  
  std::random_shuffle(std::begin(pile), std::end(pile));
}
 
Card DrawPile::drawCard() {
  Card temp = *(pile.end()-1);
  pile.pop_back();
  return temp;
}

void DrawPile::setRand(bool shuffle) {
  rand = shuffle;
}
