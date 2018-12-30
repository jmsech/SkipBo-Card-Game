#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "FaceUpPile.h"
#include "Hand.h"
#include "Player.h"


Player::Player(std::string name) : name(name) {
  //fill vector of all players piles (not hand)
  ppile.push_back(discard1);
  ppile.push_back(discard2);
  ppile.push_back(discard3);
  ppile.push_back(discard4);
}

  
// for live game play - must not change!
void Player::display() const {
  std::cout << "Current ";
  std::cout << name << ":  Stock{0}: " ;
  stock.display();
  std::cout << std::endl;
  std::cout << "   Discards{1-4}: ";
  for (int i = 0; i < 4; ++i) {
    ppile[i].display();
    std::cout << "  ";
  }
  std::cout << std::endl;
  std::cout << "   Hand{5-9}: ";
  hand.display();
  std::cout << std::endl;
}

/* saving state format - must not change!
PlayerName
Stock size
01 02 03  ...
...
Hand size
01 02 03 04 05
Discard1 size
01 02 03 04 ...
...
Discard2 size
...
Discard3 size
...
Discard4 size
...
*/
std::string Player::toString() const {
  std::stringstream result;
  result << name << "\n";
  result << "Stock " << stock.toString();
  result << "Hand " << hand.toString();
  for (int i = 0; i < 4; ++i) {
    result << "Discard" << i << " " << ppile[i].toString();
  }
  return result.str();
}

Card Player::drawCard(const int i){
  if ( i > 4) { //take card from hand
    return hand.drawCard(i);
  } else if (i == 0) {//take card from draw
    return stock.drawCard();
  } else {
    //take card from one of discard
    return ppile[i-1].drawCard();
  }
}

bool Player::addCard(const Card& c, const int goingTo) {
  if ( goingTo > 4) { //add card to hand
    return  hand.addCard(c);
 
  } else if (goingTo == 0) {
    //add card to stock only for start of game
    return stock.addCard(c);
  } else if (goingTo <= 4 && goingTo > 0) { //add card to  one of discard
    return ppile[goingTo-1].addCard(c);
  } else {
    return false;
  }
}

void Player::readIn(std::istream& is) {
  std::string current;
  is >> current; //moves is from Player name to Stock
  //call readIn for Stock, Hand,  and each Draw pile
  stock.readIn(is);
  is >> current; //move is to 'Hand'
  hand.readIn(is);
  is >> current; //move is to 'Discardi'
  for (int i = 0; i < 4; i++) {
    ppile[i].readIn(is);
    is >> current; //moves is to next 'Discardi'
  }
}

void Player::eraseCard(int cardNum) {
  if (cardNum == 0) {
    stock.eraseCard();
  } else if (cardNum >= 1 && cardNum <= 4) {
    ppile[cardNum-1].eraseCard();
  } else if (cardNum >= 5 && cardNum <= 9) {
    hand.eraseCard(cardNum);
  }   
}

bool Player::discardExists(int num) {
  return ppile[num-1].size() > 0;
}
