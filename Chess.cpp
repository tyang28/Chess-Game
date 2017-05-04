#undef FOR_RELEASE

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>
#include "Game.h"
#include "Chess.h"
#include "Prompts.h"


//Saves the game to a file.
void ChessGame::saveGame() {
	std::ofstream fp;
	std::string fileName;
	Prompts prompt = Prompts();
	prompt.saveGame();
	std::cin >>fileName;
	fp.open(fileName);
	fp << "chess" << std::endl;
	fp << m_turn << std:: endl;
	int owner;
	int row;
	char col;
	int id;

	for (int i = 7; i > -1; --i) {
     	   for(size_t j = 0; j < 8; ++j){
	    	Piece* current = getPiece(Position(j,i));
		if(current->owner() != 2) {
		    owner = current->owner();
		    row = i + 1;
		    col = j + 97;
		    if(current->id() <= 6) {
		        id =  current->id() - 1;
		    } else {
			id = current->id();
		    }

	            fp << owner << " " << col << row << " " << id << std::endl;
		    
		}
	    }
	}

        fp.close();


}

//Loads a chess game from a given file.
void ChessGame::loadGame() {
	std::ifstream fp;
	std::string fileName;
	std::cin >> fileName;
	fp.open(fileName);
	std::string line;
	std::getline (fp, line);
	std::getline (fp, line);
	m_turn = std::stoi(line);
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
	for (int i = 7; i > -1; --i) {
     	   for(size_t j = 0; j < 8; ++j){
		if(!getPiece(Position(i,j))) {
		    m_pieces[index(Position(i,j))] = newPiece(0, SPACE);
		}
	   }
	}
	fp.close();
}


//Returns true if the person whose turn it is, is in check.
int ChessGame::inCheck() {
	int turn = playerTurn();
	Position king;
	for (int i = 7; i > -1; --i) {
     	   for(size_t j = 0; j < 8; ++j){
	 	  if(getPiece(Position(j,i))->owner() == turn && 
			(getPiece(Position(j,i))->id() == 6)) {
			king = Position(j,i);
			break;
		  }
	   }
	}
	for (int i = 7; i > -1; --i) {
     	   for(size_t j = 0; j < 8; ++j){
		  Position current = Position(j,i);
		  if(getPiece(current)->owner() != playerTurn()) {
	 	     if(getPiece(Position(j,i))->validMove(current ,king, *this) == 1) {
			 return 1;
		     }
		  }
	   }
	}
	
	return 0;

}

//returns true of the player is moving themself into check.
int ChessGame::moveToCheck(Position start, Position end) {
	Piece* orgEnd = m_pieces[index(end)];
	m_pieces[index(end)] = getPiece(start);
        m_pieces[index(start)] = newPiece(0, SPACE);
	if(inCheck()) {
		m_pieces[index(start)] = m_pieces[index(end)];
		m_pieces[index(end)] = orgEnd;
		return 1;
	}
	m_pieces[index(start)] = m_pieces[index(end)];
	m_pieces[index(end)] = orgEnd;
	return 0;

}


//returns true if a stalemate occured
int ChessGame::stalemate() {
	for (int startrow = 7; startrow > -1; --startrow) {
     	   for(size_t startcol = 0; startcol < 8; ++startcol){
	     if(getPiece(Position(startcol, startrow))->owner() == playerTurn()) {
		for (int endrow = 7; endrow > -1; --endrow) {
     	           for(size_t endcol = 0; endcol < 8; ++endcol){
		       if(getPiece(Position(startcol, startrow))->validMove(Position(startcol, startrow), Position(endcol, endrow), *this) >= 0
			  && (startcol != endcol || startrow !=endrow)){
			  if(!moveToCheck(Position(startcol, startrow), Position(endcol, endrow))) {

			  return 0;
			  }
		      }
		   }
		}
	     }
	   }
	}
	return 1;
}


// Make a move on the board. Return an int, with < 0 being failure
int ChessGame::makeMove(Position start, Position end) {
    int retCode = 0;
    Piece* startpiece = getPiece(start);
    Prompts prompt = Prompts();
    if((startpiece->validMove(start, end, *this)) >= 0){
	
	if(inCheck()) {
	   Piece* orgEnd = m_pieces[index(end)];
	   m_pieces[index(end)] = getPiece(start);
           m_pieces[index(start)] = newPiece(0, SPACE);
	   if(inCheck()) {
		prompt.mustHandleCheck();
		m_pieces[index(start)] = m_pieces[index(end)];
		m_pieces[index(end)] = orgEnd;
		return -1;
	   }
	}

	if(moveToCheck(start, end)) {
		prompt.cantExposeCheck();
		return -1;
	} else {

	   if(getPiece(end)->owner() != 2 ) {
	       if(getPiece(start)->owner() != getPiece(end)->owner()) {
	           prompt.capture(playerTurn());
	       }
           }
           m_pieces[index(end)] = startpiece;
           m_pieces[index(start)] = newPiece(0, SPACE);
           retCode = 0;
	}
	
     } else if((startpiece->validMove(start, end, *this)) == -2) {
	   prompt.blocked();
	   return -1;

     }  else {
        prompt.illegalMove();
        retCode = -1;

      }

    if(getPiece(end)->id() == 1 && ((getPiece(end)->owner() == 0 && end.y == 7)
	|| (getPiece(end)->owner() == 1 && end.y == 0)) ) {
	m_pieces[index(end)] = newPiece(5, playerTurn());
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
    int board = 0;

    while(1) {
	    prompt.playerPrompt(playerTurn(), m_turn);
            std::getline (std::cin, move);

	    if(move.compare("save") == 0 ) {
		saveGame();
		prompt.playerPrompt(playerTurn(), m_turn);
                std::getline (std::cin, move);
		std::getline (std::cin, move);
	    }

	    if(move.compare("board") == 0) {
		board = !(board);
		prompt.playerPrompt(playerTurn(), m_turn);
		std::getline (std::cin, move);
	    }

	    if(move.compare("q") == 0) {
		return;
	    }
	    if(move.at(0) > 96 && 48 < move.at(1) && move.at(1) < 96 && move.at(2) == ' ' 
		&& move.at(3) > 96 && move.at(4) > 48 && move.at(4) < 96 && move.length() == 5) {
	    	Position start = Position((move.at(0) - 97), (move.at(1) - '1'));
	    	Position end = Position((move.at(3) - 97), (move.at(4) - '1'));
	    	if(validPosition(start) && validPosition(end)) {
			if(getPiece(start)->owner() != playerTurn()) {
				prompt.noPiece();
			} else {
	    	    	if( makeMove(start, end) >= 0) {
		    	 	m_turn++;
				if(!inCheck()) {
					if(stalemate()) {
				     	    prompt.staleMate();
				     	    return;
					}
				} else if (inCheck()) { 
					if (stalemate()) {
	  			     		prompt.checkMate(static_cast<Player>((m_turn % 2)));
				    		 return;
					}
				}
		     	 	if(inCheck()) {
			     	prompt.check(static_cast<Player>((m_turn % 2)));
		         	}
		     
		     
 	            	}
			}
	    	} else {
   			prompt.outOfBounds();
	    	}
	
	    } else {
		prompt.parseError();
	    }
	    if(board) {
	     printBoard();
	    }
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
    Prompts prompt = Prompts();
    int input;
    prompt.menu();
    
    while(1){
	scanf(" %d", &input);
        if (input == 2) {
	    prompt.loadGame();
	    chess.loadGame();
	    chess.run();
	    break;
        } else if( input != 1) {
	    prompt.menu();
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
