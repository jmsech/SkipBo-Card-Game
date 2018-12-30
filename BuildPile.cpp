#include "BuildPile.h"
#include <vector>

bool BuildPile::addCard(const Card& c) {
  if ((c.getValue() - pile.size() == 1) || (c.getValue() == 0)){ 
    pile.push_back(c);
    return true;
  } else {
    return false;
  }
}

//pull from the end of the vector (top of the deck)
Card BuildPile::getCard() {
  Card temp = *(pile.end()-1);
  pile.pop_back();
  return temp;
}  
