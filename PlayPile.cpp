#include <vector>
#include "PlayPile.h"

Card PlayPile::drawCard() {
  return pile[pile.size()-1];
}

void PlayPile::eraseCard(){
  pile.pop_back();
}






