#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include "SkipBoGame.h"

using std::cout;
using std::endl;


//new game constructor
SkipBoGame::SkipBoGame(bool shuffle, int nump, int stock_size, std::istream& infile): shuffle(shuffle), nump(nump), stock_size(stock_size), infile(infile) {
  curp = 0;
  if (!shuffle) {
    draw.setRand(shuffle); //change shuffle type to false if needed
  }
  //fill draw pile with all 162 cards; shuffle if specified
  int c;
  while (infile >> c) {
    draw.addCard(c);
  }
  if (shuffle) {
    draw.shuffle();
  }
 
  //put build piles in build vector
  build.push_back(build_a);
  build.push_back(build_b);
  build.push_back(build_c);
  build.push_back(build_d);


  //initialize each Player
  std::string name;
  for (int i = 0; i < nump; i++) {
    name = "Player" + std::to_string(i);
    Player play(name); //initialize each player
    peep.push_back(play); //add to players vector
  }
  
  deal();

}

//for saved game
SkipBoGame::SkipBoGame(bool shuffle, std::istream& infile): shuffle(shuffle), infile(infile) {
  if (!shuffle) {
    draw.setRand(shuffle); //change shuffle type to false if needed
  }
  
  //put build piles in build vector
  build.push_back(build_a);
  build.push_back(build_b);
  build.push_back(build_c);
  build.push_back(build_d);

  readIn(infile);
  if (shuffle) {
    draw.shuffle();
  }
}
  
void SkipBoGame::fillHand(){
  while(peep[curp].getHandSize() < 5){
    peep[curp].addCard(draw.drawCard(), 5);
    if(checkDraw()) {
      cout << "draw pile full, refilled" << endl;
    }
  }
}



bool SkipBoGame::fillExtra(BuildPile& buildP){ 
  if(buildP.size() == 12){
    for(int i = 0; i < 12; i++){
      extraPile.addTop(buildP.getCard(),i);
    }
    return true;
  }
  else{
    return false;
 }
}
  
/* for live game play - must not change format!
   
   drawPile  build_a  build_b  build_c  build_d
   playerName  stock_0  
   discards: discard_1 discard_2 discard_3 discard_4
   hand: card_5 card_6 card_7 card_8 card_9
*/
void SkipBoGame::display() const {
  std::cout << "Draw: ";
  draw.display();
  std::cout << "  Build Piles: ";
  for (int j = 0; j < 4; j++) {
    build[j].display();
    std::cout << " ";
  }
  std::cout << std::endl;
  peep[curp].display();
}

/* for saving state - must not change format!

shuffle numplayers currplayer
PlayerCurp [display]
PlayerCurp+1 [display]
[etc for all players]
Draw [display]
Build_a [display]
Build_b [display]
Build_c [display]
Build_d [display]
*/
std::string SkipBoGame::toString() const {
  std::stringstream result;
  int idx;
  result << draw.getRand() << " " << nump << " " << curp << "\n";
  for (int i = 0; i < nump; ++i) {
    idx = (curp+i) % nump;
    result << peep[idx].toString();
  }
  result << "Draw " << draw.toString(); 
  for (int j = 0; j < 4; j++) {
    result << "Build_" << char('a'+j) << " ";
    result << build[j].toString();  
  }
  return result.str();
	      }

void SkipBoGame::readIn(std::istream & is){
  std::string current;
  //ignore saved shuffle state; use command line arg
  is >> current >> nump >> curp; 
  std::string name;
  for (int i = 0; i < nump; i++) {
    name = "Player" + std::to_string(i);
    Player play(name); //initialize each player
    peep.push_back((Player)name); //add to players vector
  }
  
  is >> current; //move is to name of current Player
  //readIn each player starting with curp
  for (int i = 0, temp = curp; i < nump; i++, temp++) {
    if (temp == nump) {
      temp = 0;
    }
    peep[temp].readIn(is);
  }
  //read in draw pile and build piles
  draw.readIn(is);
  for (int i = 0; i < 4; i++) {
    build[i].readIn(is);//move is to next 'Build'
  }
}

//deal cards in loop at the start of a new game
void SkipBoGame::deal() {
  //fill stock pile (player pile 0) for each player
  for (int j = 0; j < stock_size; j++) {
    for (int i = 0; i < nump; i++) {
      peep[i].addCard(draw.drawCard(), 0);
    }
  }
}

void SkipBoGame::save(std::ostream& file) {
  if (shuffle) {
    file << "true ";
  } else {
    file << "false ";
  }
  file << nump << " " << curp << std::endl;
  for (int i = 0; i < nump; i++) {
    file << peep[curp].toString();
    nextPlayer();
  }
  file << "Draw ";
  int size = extraPile.size();
  for(int i = 0; i < size; i++) {
    draw.addTop(extraPile.drawCard(), i);
  }
  if(shuffle){
    draw.shuffle();
  }
  file << draw.toString();

  for (int i = 0; i < 4; i++) {
    file << "Build_" << (char)('a' + i) << " ";
    file << build[i].toString();
  }
}

bool SkipBoGame::move(char ifBuild, char goingTo) {
  int digit;
  int comingFrom;
  bool ifValid;
  if(isdigit(goingTo) && isdigit(ifBuild)){
    digit = (int)goingTo - 48;
    comingFrom = (int)ifBuild - 48;
    if (comingFrom > 9 || comingFrom < 0) { //illegal
      return false;
    } else if(digit <= 9 && digit > 0) { //going to a pile in Player
      if(comingFrom <= 4){
	return false;
      }
      //hand to discard
      if (comingFrom > peep[curp].getHandSize() + 4) {
	return false;
      }
      ifValid = peep[curp].addCard(peep[curp].drawCard(comingFrom), digit);
      if(ifValid){
	peep[curp].eraseCard(comingFrom);
      }
      return ifValid;
    }
    else{
      return false;
    }
  }else if(isdigit(ifBuild)){
    comingFrom = (int) ifBuild - 48;
    if (comingFrom > 9 || comingFrom < 0) { //illegal 
      return false;
    }
    //check if card exists in hand position
    if (comingFrom > peep[curp].getHandSize() + 4) {
      return false;
    }
    //check if card exists in discard
    if ((comingFrom < 5) && (comingFrom > 0) && !peep[curp].discardExists(comingFrom)) {
      return false;
    }
    if (goingTo == 'a') { //going to a build Pile
      ifValid = build[0].addCard(peep[curp].drawCard(comingFrom));
      if (ifValid) {
	peep[curp].eraseCard(comingFrom);
	if(fillExtra(build[0])){
	  cout << "build pile " << (char)goingTo << " full, set aside" << endl;
	}
      }
      return ifValid;
    }else if (goingTo == 'b') { //going to b build Pile
      ifValid = build[1].addCard(peep[curp].drawCard(comingFrom));
      if (ifValid) {
        peep[curp].eraseCard(comingFrom);
	if(fillExtra(build[1])){
          cout << "build pile " << (char)goingTo << " full, set aside" << endl;
        }
      }
      return ifValid;
    }else if (goingTo == 'c') { //going to c build Pile
      ifValid = build[2].addCard(peep[curp].drawCard(comingFrom));
      if (ifValid) {
        peep[curp].eraseCard(comingFrom);
	if(fillExtra(build[2])){
          cout << "build pile " << (char)goingTo << " full, set aside" << endl;
        }
      }
      return ifValid;
    }else if (goingTo == 'd') { //going to d build Pile
      ifValid = build[3].addCard(peep[curp].drawCard(comingFrom));
      if (ifValid) {
        peep[curp].eraseCard(comingFrom);
	if(fillExtra(build[3])){
          cout << "build pile " << (char)goingTo << " full, set aside" << endl;
        }
      }
      return ifValid;
    }else{
      return false;
    }
  }
  return false;
}

void SkipBoGame::nextPlayer() {
  curp++;//goes to next player
  if(curp == nump){ //goes through next round
      curp = 0;
  }
}


bool SkipBoGame::checkDraw() {
  Card temp;
  if (draw.size() == 0) {
    int size = extraPile.size();
    for(int i = 0; i < size; i++) {
      draw.addCard(extraPile.drawCard());
    }
    if (shuffle) {
      draw.shuffle();
    }
    return true;
  }
  return false;
}
