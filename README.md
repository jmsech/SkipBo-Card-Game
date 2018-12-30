# SkipBo-Card-Game
A 2-6 player Matel card game

Object oriented design:   
		
	PlayPile and BuildPile --IS A--> FaceUpPile
	Hand, FaceUpPile, and DrawPile --IS A--> Pile
    
  	Player <>--HAS A-- Hand and 5x PlayPile (1x stock pile, 4x discard pile
  	SkipBoGame <>--HAS A -- 2-6x Player, 2xDrawPile (draw pile and filled discard pile), 4xDrawPile
 
 
 Start new game: 
    
    ./skipbo...
 
    argv[1]: true/false -indicates whether the deck should be shuffled   
    argv[2]: 2-6 - number of players
    argv[3]: 10-30 - number of cards dealt to each players stock pile; must be <=20 for 6 players
    argv[4]: deck.txt - starting deck file
    
  Load Saved Game: 
  
    ./skipbo...
    
    argv[1]: true/false - if the deck should be shuffled before initializing game
    argv[2]: savedGameFile - a .txt file filled from a previously saved game
