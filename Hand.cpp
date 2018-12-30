#include <iostream>
#include "Hand.h"

/*************************************
For SkipBo - Fall 2018 - EN.601.220
Instructor provided code
*************************************/

// for live game play - must not change!
void Hand::display() const {
  int i;
  for (i = 0; i < size(); i++) {
    pile[i].display();
    std::cout << "  ";
  }
  for ( ; i < 5; i++)
    std::cout << "--  ";
}

bool Hand::addCard(const Card& c){
  if((int)pile.size() < MAXSIZE){
    pile.push_back(c);
    return true;
  }else{
    return false;
  }
}

Card Hand::drawCard(const int i) {
  Card temp(pile[i - 5].getValue());
  return temp; 
}

void Hand::eraseCard(int i){
  pile.erase(pile.begin() + i - 5);
}
