#ifndef _PLAYER_H
#define _PLAYER_H

#include <iostream>
#include <vector>
#include <string>
#include "PlayPile.h"
#include "Hand.h"

class Player {
 private:
  std::string name;
  PlayPile stock, discard1, discard2, discard3, discard4;
  std::vector<PlayPile> ppile;
  Hand hand;
  
 public:
  Player(std::string name);
  
  std::string toString() const;  // calls toString of all piles for saving
  
  int getStockSize() const {return stock.size();}

  void readIn(std::istream & is);
  
  // remove card from player pile i 
  Card drawCard(const int i);

  //add a card to hand, stock, or discard;
  //used to fill Player initially, and move cards throughout game
  bool addCard(const Card& c, const int goingTo);

  void display() const;  // display all piles

  std::string getName() const {return name;}

  int getHandSize() const {return hand.size();}

  void eraseCard(int cardNum);

  bool discardExists(int num);
};


#endif
