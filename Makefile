CONSERVATIVE_FLAGS = -std=c++11 -Wall -Wextra -pedantic
0;136;0cDEBUGGING_FLAGS = -g -O0
CFLAGS = $(CONSERVATIVE_FLAGS) $(DEBUGGING_FLAGS)

skipbo: main.o SkipBoGame.o Card.o Pile.o Hand.o DrawPile.o FaceUpPile.o PlayPile.o BuildPile.o Player.o
	g++ -o skipbo main.o SkipBoGame.o Card.o Pile.o Hand.o DrawPile.o FaceUpPile.o PlayPile.o BuildPile.o Player.o

main.o: main.cpp
	g++ -c main.cpp $(CFLAGS)

SkipBoGame.o: SkipBoGame.cpp SkipBoGame.h 
	g++ -c SkipBoGame.cpp $(CFLAGS)

Card.o: Card.cpp Card.h
	g++ -c Card.cpp $(CFLAGS)

Pile.o: Pile.cpp Pile.h
	g++ -c Pile.cpp $(CFLAGS)

DrawPile.o: DrawPile.cpp DrawPile.h
	g++ -c DrawPile.cpp $(CFLAGS)

Hand.o: Hand.cpp Hand.h
	g++ -c Hand.cpp $(CFLAGS)

FaceUpPile.o: FaceUpPile.cpp FaceUpPile.h
	g++ -c FaceUpPile.cpp $(CFLAGS)

PlayPile.o: PlayPile.cpp PlayPile.h
	g++ -c PlayPile.cpp $(CFLAGS)

BuildPile.o: BuildPile.cpp BuildPile.h
	g++ -c BuildPile.cpp $(CFLAGS)

Player.o: Player.cpp Player.h
	g++ -c Player.cpp $(CFLAGS)


.PHONY: clean
clean:
	rm -f *.o skipbo? *~ *#
