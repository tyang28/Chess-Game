CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic -std=c++11 -g

chess: Chess.o Board.o main.o
	$(CXX) $(CXXFLAGS) main.o Chess.o Board.o -o chess
unittest: Chess.o Board.o unittest.o
	$(CXX) $(CXXFLAGS) unittest.o Chess.o Board.o -o unittest

Board.o: Game.h
Chess.o: Game.h Chess.h Prompts.h
main.o: Game.h Chess.h Prompts.h main.cpp
unittest.o: Game.h Chess.h Prompts.h unittest.cpp

clean:
	rm *.o chess

