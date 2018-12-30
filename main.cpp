#include <iostream>
#include "SkipBoGame.h"
#include <vector>
#include <string>
#include <fstream>

using std::stoi;
using std::string;
using std::cout;
using std::cin;
using std::vector;
using std::endl;

int playGame(SkipBoGame& game);


int main(int argc,char* argv[]){
  string error = "invalid program usage: ";
  std::ifstream file;
  string ifShuffle = argv[1];
  bool shuffle;

  if(ifShuffle == "false"){
    shuffle = false;
  }else if(ifShuffle == "true"){
    shuffle = true;
  }else{
    cout << error << "invalid first argument" << endl;
    return 1;
  }

  ///////////////////Load Saved Game////////////////////////
  if(argc == 3){
    file.open(argv[2], std::ifstream::in);
    if(!file.is_open()){
      cout << error << "can't open input game file" << endl;
      return 1;
    }
    SkipBoGame g(shuffle, file);
    if (playGame(g)) {
      file.close();
      return 1;
    } else {
      file.close();
      return 0;
    }
     
  ///////////Start New Game/////////////////////////////// 
  }else if(argc == 5){//for new game
      //check corrent player numbers
    int numPlayers = stoi(argv[2]);
    int stockSize = stoi(argv[3]);
    if(numPlayers >= 2 && numPlayers <= 6){
      cout << "num players is " << numPlayers << endl;
    } else {
      cout << error << "num players must be 2-6" << endl;
      return 1;
    }
    //check bad stock size
    if((stockSize < 1) || (stockSize > 30)){
      cout << error << "bad stock size" << endl;
      return 1;
    } else if (stockSize >= 20 && numPlayers == 6) {
      cout << error << "bad stock size" << endl;
      return 1;
    }
    
    cout << "stock size is " << stockSize << endl;
    //open deck file
    file.open(argv[4], std::ifstream::in);
    if(!file.is_open()){
      cout << error << "can't open deck file" << endl;
      return 1;
    }
    SkipBoGame g(shuffle, numPlayers, stockSize, file);
    file.close();
    if (playGame(g)) {
      return 1;
    } else {
      return 0;
    }
    
  } else{//if there is not the right amount of arguments
    cout << error << "invalid number of arguments" << endl;  
    return 1;
  }
  return 0;
}



int playGame(SkipBoGame& game) {

   /////////////////////Game Play///////////////////////////////////////////

  //copies correct game so its in this scope

  int playerNumber; //gets current player (might not be 0 for saved game)
  string input;
  char commingFrom;
  char goingTo;

  cout << endl;
  while(true){
    input = "q";
    playerNumber = game.getCurp();
    // cout << endl;
    cout << " >> Player" << playerNumber << " turn next" << endl;
    //says which player it is
    cout << "(p)lay, (s)ave, or (q)uit ? ";
    cin >> input;
    if(input == "q"){
      cout << "thanks for playing" << endl;//if they want to quit
      return 0;
    }else if(input == "s"){//if user wants to save
      std::string outfile;
      cout << "save filename: ";
      cin >> outfile; //opens the outfile
      std::ofstream file;
      file.open(outfile, std::ofstream::out);
      if (file.is_open()) {
        game.save(file);//saves game
        file.close();
        return 0;
      }else{
        cout << "invalid output file" << endl;
	//outputs error if file isnt real
        return 1;
      }
      
      ////////////////Play State////////////////////////////
    } else if(input == "p"){//if user wants to play
      bool turnend = false;
      int number;
      game.fillHand();
      while (!turnend) {
	game.display();
       	cout << "(m)ove [start] [end] or (d)raw ? ";
	input = "lkjhgfdsmnbvcxwertyui";
	cin >> input;
	if (input == "lkjhgfdsmnbvcxwertyui") {
	  cout << "\nthanks for playing" << endl;
	  return 0;
	}
	if(input == "m"){//if they want to move
	  cin >> commingFrom;
	  cin >> goingTo;
	  if(!game.move(commingFrom, goingTo)){
	    cout << "illegal command, try again" << endl; //if move is illegal
	    //check for empty stock after every move
	  } else {
	    if(game.getCurpStockSize() == 0){//ends game with winner
	      cout << endl << "GAME OVER - Player" << game.getCurp() << " wins!" << endl;
	      return 0;
	    }
	    //end turn after moving to a discard pile
	    if(isdigit(goingTo)){
	      number = (int)goingTo - 48;
	      if(number >= 1 && number <= 4){
		turnend = true;
		cout << endl;
		game.display();
		game.nextPlayer();
	      }
	    }
	  }
	  cout << endl;
	} else if(input == "d"){//if they want tot draw
	  if (game.getCurpHandSize() == 0) {
	    game.fillHand();
	  } else {
	    cout << "illegal command, try again" << endl; 
	    //if the draw is illegal
	  }
	  cout << endl;
	} else {
	  cout << "illegal command, try again" << endl;
	  //if none of the right inputs are put in
	  cout << endl;
	}
      }
    } else {
      cout << "illegal command, try again" << endl;
       //if none of the right inputs are put in
       cout << endl;
    }
  }
}
