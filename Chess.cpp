#undef FOR_RELEASE

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include "Game.h"
#include "Chess.h"
#include "Prompts.h"

// Make a move on the board. Return an int, with < 0 being failure
int ChessGame::makeMove(Position start, Position end) {
    // Possibly implement chess-specific move logic here
    //
    // We call Board's makeMove to handle any general move logic
    // Feel free to use this or change it as you see fit
    int retCode = Board::makeMove(start, end);
    const ChessGame board = *this;
    Piece* startpiece = getPiece(start);
    std::cout << start.x << start.y << " " << end.x << end.y << std::endl;
    if((startpiece->validMove(start, end, board)) >= 0){
 
      m_pieces[index(end)] = startpiece;
      m_pieces[index(start)] = newPiece(0, SPACE);
      puts("did run");
      retCode = 0;
     }
    else{
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
    
    Prompts* prompt = new Prompts();
    int input;
    prompt->menu();
    
    while(1){
	scanf(" %d", &input);
        if (input == 2) {
	    prompt->loadGame();
	    break;
	    //Add loading a game
        } else if( input != 1) {
	    prompt->menu();
        } else {
	   break;
	}
    }
    if (input == 1) {
	createBoard();
        setupBoard();
	//int whiteTurnNum = 0;
	//int blackTurnNum = 0;
	m_turn = 1;

	std::string move;
	while(1) {
	   if(playerTurn() == 0) {
		puts("test");
	        prompt->playerPrompt(playerTurn(), m_turn);
		std::getline (std::cin, move);
		std::getline (std::cin, move);
		puts("test");
		int startRow = move.at(0) - 97;
		int endRow = move.at(3) - 97;
		int startColumn = move.at(1) - '1';
	        int endColumn = move.at(4) - '1';
		std::cout << startRow << "  " << endRow << std::endl;
		Position start = Position(startRow, startColumn);
		Position end = Position(endRow, endColumn);

		std::cout << startColumn << "  " << endColumn << std::endl;
		if( makeMove(start, end) >= 0) {
		  m_turn++;
		}
		
	   }
	   break;
	 

	}
	
	

    }
    
    
    printBoard();
    puts("done printing");
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
    chess.run();
}
