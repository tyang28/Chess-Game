#undef FOR_RELEASE

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>
#include "Game.h"
#include "Chess.h"
#include "Prompts.h"


//Loads a chess game from a given file.
void ChessGame::loadGame() {
	std::ifstream fp;
	std::string fileName;
	std::cin >> fileName;
	std::cout << fileName << std::endl;
	fp.open(fileName);
	std::string line;
	std::getline (fp, line);
	std::getline (fp, line);
	m_turn = line.at(0) - '0';
	int id;
	int row;
	int col;
	int owner;
	while(std::getline (fp, line)) {
	    if(line.length() > 3) {
		owner = line.at(0) - '0';
		row = line.at(2) - 97;
		col = line.at(3) - '1';
		id = line.at(5) - 47;
		initPiece(id, (Player)owner, Position(row, col));

	    }
	}
	puts("test");
	for (int i = 7; i > -1; --i) {
     	   for(size_t j = 0; j < 8; ++j){
		if(!getPiece(Position(i,j))) {
		    m_pieces[index(Position(i,j))] = newPiece(0, SPACE);
		}
	   }
	}
	
}


//Returns true if the person whose turn it is, is in check.
int ChessGame::inCheck() {
	int turn = playerTurn();
	ChessGame board = *this;
	Position king;
	for (int i = 7; i > -1; --i) {
     	   for(size_t j = 0; j < 8; ++j){
	 	  if(getPiece(Position(i,j))->owner() == turn && 
			(getPiece(Position(i,j))->id() == 6)) {
			king = Position(i,j);
			break;
		  }
	   }
	}
	for (int i = 7; i > -1; --i) {
     	   for(size_t j = 0; j < 8; ++j){
		  Position current = Position(i,j);
	 	  if(getPiece(Position(i,j))->validMove(current ,king, board) >=0) {
			return 1;
		  }
	   }
	}
	
	return -1;

}

//returns true of the player is moving themself into check.
int ChessGame::moveToCheck(Position start, Position end) {
	Prompts prompt = Prompts();
	Piece* orgEnd = m_pieces[index(end)];
	m_pieces[index(end)] = getPiece(start);
        m_pieces[index(start)] = newPiece(0, SPACE);
	if(inCheck()) {
		prompt.cantExposeCheck();
		m_pieces[index(start)] = m_pieces[index(end)];
		m_pieces[index(end)] = orgEnd;
		return 1;
	}
	m_pieces[index(start)] = m_pieces[index(end)];
	m_pieces[index(end)] = orgEnd;
	return -1;

}

// Make a move on the board. Return an int, with < 0 being failure
int ChessGame::makeMove(Position start, Position end) {
    // Possibly implement chess-specific move logic here
    //
    // We call Board's makeMove to handle any general move logic
    // Feel free to use this or change it as you see fit
    int retCode = 0;
    //ChessGame board = *this;
    Piece* startpiece = getPiece(start);
    std::cout << start.x << start.y << " " << end.x << end.y << " "<< startpiece->owner() << std::endl;
    if((startpiece->validMove(start, end, *this)) >= 0){
      m_pieces[index(end)] = startpiece;

      m_pieces[index(start)] = newPiece(0, SPACE);
      puts("did run");
      retCode = 0;

     }  else {
      Prompts* prompt = new Prompts();
      prompt->illegalMove();
      retCode = -1;

      }
    return retCode;
}
//Create the board and fill with empty spaces
void ChessGame::createBoard() {
    for (size_t i = 0; i < 8; ++i) {
      for(size_t j = 2; j < 6; ++j){
        initPiece(SPACE_ENUM, SPACE, Position(i, j));  
      }
    }  
}  
// Setup the chess board with its initial pieces
void ChessGame::setupBoard() {
    std::vector<int> pieces {
        ROOK_ENUM, KNIGHT_ENUM, BISHOP_ENUM, QUEEN_ENUM,
        KING_ENUM, BISHOP_ENUM, KNIGHT_ENUM, ROOK_ENUM
    };
    for (size_t i = 0; i < pieces.size(); ++i) {
        initPiece(PAWN_ENUM, WHITE, Position(i, 1));
        initPiece(pieces[i], WHITE, Position(i, 0));
        initPiece(pieces[i], BLACK, Position(i, 7));
        initPiece(PAWN_ENUM, BLACK, Position(i, 6));
    }
}
void ChessGame::run() {
    
    Prompts prompt = Prompts();
    std::string move;
    std::getline (std::cin, move);
    while(1) {
	//if(playerTurn() == 0) {
	    prompt.playerPrompt(playerTurn(), m_turn);
            
	    std::getline (std::cin, move);
	    Position start = Position((move.at(0) - 97), (move.at(1) - '1'));
	    Position end = Position((move.at(3) - 97), (move.at(4) - '1'));
	    if(validPosition(start) && validPosition(end)) {

	    	if( makeMove(start, end) >= 0) {
		     puts("tester");
	 	     m_turn++;
 	        }
	    } else {
   		prompt.outOfBounds();
	    }
		
	//}
	  printBoard();
	   //break;
     }
    
    
    
}
void ChessGame::printBoard(){
    for (int i = 7; i > -1; --i) {
      for(size_t j = 0; j < 8; ++j){
	Piece* piece = getPiece(Position(j,i));
	int id = piece->id();
	std::cout << id;
      }
      std::cout<<std::endl;
    }
}
int main() {
    ChessGame chess;
    Prompts* prompt = new Prompts();
    int input;
    prompt->menu();
    
    while(1){
	scanf(" %d", &input);
        if (input == 2) {
	    prompt->loadGame();
	    chess.loadGame();
	    chess.run();
	    break;
	    //Add loading a game
        } else if( input != 1) {
	    prompt->menu();
        } else {
	   break;
	}
    }
    if (input == 1) {
	chess.createBoard();
        chess.setupBoard();
	chess.run();
    }
}
