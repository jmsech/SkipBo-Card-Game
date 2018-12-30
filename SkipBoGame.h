#ifndef _SKIPBOGAME_H
#define _SKIPBOGAME_H

#include <iostream>
#include <vector>
#include "Player.h"
#include "DrawPile.h"
#include "BuildPile.h"

class SkipBoGame {
  
 private:
  bool shuffle;
  int nump, curp, stock_size; //number of players, current player, stock
  std::istream& infile; //(nullptr);
  DrawPile draw, extraPile; //initializes to true, modify latter if needed
  BuildPile build_a, build_b, build_c, build_d;
  std::vector<BuildPile> build;
  std::vector<Player> peep;
  
 public:
  //new game constructor
 SkipBoGame(bool shuffle, int nump, int stock_size, std::istream& infile);
 //saved game constructor
 SkipBoGame(bool shuffle, std::istream& infile);
 
 //display current turn (written for us)
 void display() const;
 
 //Save current gameplay (write to file); (written for us)
 std::string toString() const;

 //a discard pile for build piles
 bool fillExtra(BuildPile& buildP);
 //Start from a saved game
 void readIn(std::istream & is);
 
 //called at the begginning of a new game
 void deal();
 
 void save(std::ostream& file);
 
 //bool move(int comingFrom, int goingTo);
 
 bool move(char ifBuild, char goingTo);
 
 int getCurp() const{ return curp; }
 
 std::string getCurpName() const { return peep[curp].getName(); }

 //moves curp to next player
 void nextPlayer();
 
 int getCurpHandSize() const { return peep[curp].getHandSize(); }
 
 int getCurpStockSize() const{ return peep[curp].getStockSize(); } 
 
 //fills hand automatically at the start of every turn; otherwise can only draw when you have an empty hand
 void fillHand();

 //checks if drawPile mepty, fills from extraPile
 bool checkDraw();
 
};

#endif  
