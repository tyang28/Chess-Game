#ifndef CHESS_H
#define CHESS_H

#include "Game.h"
#include "Prompts.h"
// Game status codes
// -----------------
// These enumerations are optional. You can choose to use them,
// or you can decide they're not needed. They *could* be used, for
// example, to return values from validMove() and makeMove(), and
// any other methods you want. But so long as you follow the conventions
// of those methods (>0 is success, <0 is failure), you're free to
// do things your own way.
enum status {
    LOAD_FAILURE = -10,
    SAVE_FAILURE,
    PARSE_ERROR,
    MOVE_ERROR_OUT_OF_BOUNDS,
    MOVE_ERROR_NO_PIECE,
    MOVE_ERROR_BLOCKED,
    MOVE_ERROR_CANT_CASTLE,
    MOVE_ERROR_MUST_HANDLE_CHECK,
    MOVE_ERROR_CANT_EXPOSE_CHECK,
    MOVE_ERROR_ILLEGAL,
    SUCCESS = 1,
    MOVE_CHECK,
    MOVE_CAPTURE,
    MOVE_CHECKMATE,
    MOVE_STALEMATE,
    GAME_WIN,
    GAME_OVER
};



// Possible pieces
enum PieceEnum {
    PAWN_ENUM = 0,
    ROOK_ENUM = 1,
    KNIGHT_ENUM = 2,
    BISHOP_ENUM = 3,
    QUEEN_ENUM = 4,
    KING_ENUM = 5
};
class MysteryPiece : public Piece {
protected:
    friend PieceFactory<MysteryPiece>;
    MysteryPiece(Player owner, int id) : Piece(owner, id) {}
public:
    // This method will have piece-specific logic for checking valid moves
    // It may also call the generic Piece::validMove for common logic
    int validMove(Position, Position,
        const Board&) const override {
        return SUCCESS;
    }
};

class Pawn : public Piece {
protected:
    friend PieceFactory<Pawn>;
    Pawn(Player owner, int id) : Piece(owner, id) {}
public:
    // This method will have piece-specific logic for checking valid moves
    // It may also call the generic Piece::validMove for common logic
    int validMove(Position start, Position end,
        const Board& board) const override {
        Piece* startpiece = board.getPiece(start);
	Piece* endpiece = board.getPiece(end);

        if(endpiece != nullptr && startpiece->owner() == endpiece->owner()){
	  return -2;
        }

	if(endpiece != nullptr && (startpiece->owner() == 0) && (endpiece->owner() == 1)){
	  if((end.x == start.x + 1) && (end.y == start.y + 1)){
	    return SUCCESS; 
	  }
	  else if((end.x == start.x - 1) && (end.y == start.y + 1)){
	    return SUCCESS;
	  }
	  else{
	    return -1;
	  }
	}

	if(endpiece != nullptr &&(startpiece->owner() == 1) && (endpiece->owner() == 0)){
	  if((end.x == start.x + 1) && (end.y == start.y - 1)){
            return SUCCESS;
          }
          else if((end.x == start.x - 1) && (end.y == start.y - 1)){
            return SUCCESS;
          }
          else{
            return -1;
          }
	}

	if((startpiece->owner() == 0) && (endpiece == nullptr)){
	  //WHITE SINGLE SPACE
	  if(startpiece->owner() == 0){
            if(((start.x - end.x) == 0)&& ((end.y - start.y) == 1)){
              return SUCCESS;
            }
          }
	  //WHITE DOUBLE SPACE
	  if(start.y == 1){
            if(((end.y - start.y) == 2)&&((start.x - end.x) == 0)){
              return SUCCESS;
            }
          }
	}

	//BLACK DOUBLE SPACE
	if((startpiece->owner() == 1) && (endpiece == nullptr)){
	  //BLACK SINGLE SPACE                                                                                                                                                                           
          if(startpiece->owner() == 1){
            if(((start.x - end.x) == 0)&& ((start.y - end.y) == 1)){
              return SUCCESS;
            }
          }
	  //BLACK DOUBLE SPACE
	  if(start.y == 6){
            if(((start.y - end.y) == 2)&&((start.x - end.x) == 0)){
	      return SUCCESS;
            }
	  }
        }
	
	return -1;
    }
    
};
class Rook : public Piece {
protected:
    friend PieceFactory<Rook>;
    Rook(Player owner, int id) : Piece(owner, id) {}
public:
    // This method will have piece-specific logic for checking valid moves
    // It may also call the generic Piece::validMove for common logic
    int validMove(Position start, Position end,
        const Board& board) const override {
        Piece* startpiece = board.getPiece(start);                                                                                                                                                       
        Piece* endpiece = board.getPiece(end);
	unsigned int a = start.y + 1;
	unsigned int b = start.y - 1;
	unsigned int c = start.x + 1;
	unsigned int d = start.x - 1;
        if(endpiece != nullptr && startpiece->owner() == endpiece->owner()){
	  return -2;
        }
        else if(endpiece == nullptr || startpiece->owner() != endpiece->owner()){
          if((start.x == end.x)&&((end.y - start.y) < 8)){
	    if(end.y > start.y){
	      for(;a < end.y; ++a){
	        Piece* betweenpiece = board.getPiece(Position(start.x,a));
	        if(betweenpiece != nullptr){
		  return -2;
	        }
	      }
	      return SUCCESS;
	    }
     	  }
	  //MOVING DOWN
	  if((start.x == end.x)&&((start.y - end.y) < 8)){
            if(start.y > end.y){
              for(;b > end.y; --b){
                Piece* betweenpiece = board.getPiece(Position(start.x,b));
                if(betweenpiece != nullptr){
                  return -2;
                }
              }
              return SUCCESS;
            }
          }
	  //MOVING RIGHT
	  if((start.y == end.y)&&((end.x - start.x) < 8)){
	    if(end.x > start.x){
	      for(;c < end.x; ++c){
		Piece* betweenpiece = board.getPiece(Position(c, start.y));
		if(betweenpiece != nullptr){
		  return -2;
		}
	      }
	      return SUCCESS;
	    }
	  }
	  //MOVING LEFT
	  if((start.y == end.y)&&((start.x - end.x) < 8)){
            if(start.x > end.x){
              for(;d > end.x; --d){
                Piece* betweenpiece = board.getPiece(Position(d, start.y));
                if(betweenpiece != nullptr){
                  return -2;
                }
              }
              return SUCCESS;
            }
          }
        }
        return -1;
    }
};
class Knight : public Piece {
protected:
    friend PieceFactory<Knight>;
    Knight(Player owner, int id) : Piece(owner, id) {}
public:
    // This method will have piece-specific logic for checking valid moves
    // It may also call the generic Piece::validMove for common logic
    int validMove(Position start, Position end,
        const Board& board) const override {
        Piece* startpiece = board.getPiece(start);
        Piece* endpiece = board.getPiece(end);
        if(endpiece != nullptr && startpiece->owner() == endpiece->owner()){
          return -2;
        }
	else if(endpiece == nullptr || startpiece->owner() != endpiece->owner()){
	  if(end.y > start.y){
	    if((end.y == (start.y + 2))&&(end.x == (start.x + 1))){
	      return SUCCESS;
	    }
	    else if((end.y == (start.y + 1))&&(end.x == (start.x + 2))){
	      return SUCCESS;
	    }
	    else if((end.y == (start.y + 2))&&(end.x == (start.x - 1))){
	      return SUCCESS;
	    }
	    else if((end.y == (start.y + 1))&&(end.x == (start.x - 2))){
              return SUCCESS;
            }
	  }
	  if(end.y < start.y){
	    if((end.y == (start.y - 2))&&(end.x == (start.x + 1))){
	      return SUCCESS;
	    }
	    else if((end.y == (start.y - 1))&&(end.x == (start.x + 2))){
	      return SUCCESS;
	    }
	    else if((end.y == (start.y - 2))&&(end.x == (start.x - 1))){
              return SUCCESS;
            }
	    else if((end.y == (start.y - 1))&&(end.x == (start.x - 2))){
              return SUCCESS;
            }
	  }
        }
        return -1;
    }
};
class Bishop : public Piece {
protected:
    friend PieceFactory<Bishop>;
    Bishop(Player owner, int id) : Piece(owner, id) {}
public:
    // This method will have piece-specific logic for checking valid moves
    // It may also call the generic Piece::validMove for common logic
    int validMove(Position start, Position end,
        const Board& board) const override {
        Piece* startpiece = board.getPiece(start);
        Piece* endpiece = board.getPiece(end);
        if( endpiece != nullptr && startpiece->owner() == endpiece->owner()){
          return -2;
        }
	else if(endpiece == nullptr || startpiece->owner() != endpiece->owner()){
	  //TOP RIGHT DIAGONALS
	  unsigned int xcoord1 = start.x + 1;
	  unsigned int ycoord1 = start.y + 1;
	  unsigned int xcoord2 = start.x - 1;
	  unsigned int ycoord2 = start.y - 1;
	  if((((int)end.x - start.x) > 0) &&(((int)end.y - start.y) > 0)){
	    if((end.x - start.x) == (end.y - start.y)){
	      while((end.x > xcoord1)&&(end.y > ycoord1)){
	        Piece* betweenpiece = board.getPiece(Position(xcoord1, ycoord1));
	        if(betweenpiece  != nullptr){
	          return -2;
	        }
	        ++xcoord1;
	        ++ycoord1;
	      }
	    return SUCCESS;
	    }
	  }
	  //TOP LEFT DIAGONALS
          if((((int)start.x - end.x) > 0) &&(((int)end.y - start.y) > 0)){
            if((start.x - end.x) == (end.y - start.y)){
              while((end.x < xcoord2)&&(end.y > ycoord1)){
                Piece* betweenpiece = board.getPiece(Position(xcoord2, ycoord1));
                if(betweenpiece != nullptr){
                  return -2;
                }
                --xcoord1;
                ++ycoord1;
              }
            return SUCCESS;
            }
          }
	  
	  //BOTTOM RIGHT DIAGONALS
	  if((((int)end.x - start.x) > 0) &&(((int)start.y - end.y) > 0)){
            if((end.x - start.x) == (start.y - end.y)){
              while((end.x > xcoord1)&&(end.y < ycoord2)){
                Piece* betweenpiece = board.getPiece(Position(xcoord1, ycoord2));
                if(betweenpiece != nullptr){
                  return -2;
                }
                ++xcoord1;
                --ycoord1;
              }
            return SUCCESS;
            }
          }
	  //BOTTOM LEFT DIAGONALS
	  if((((int)start.x - end.x) > 0) &&(((int)start.y - end.y) > 0)){
            if((start.x - end.x) == (start.y - end.y)){
              while((end.x < xcoord2)&&(end.y < ycoord2)){
                Piece* betweenpiece = board.getPiece(Position(xcoord1, ycoord2));
                if(betweenpiece != nullptr){
                  return -2;
                }
                --xcoord1;
                --ycoord1;
              }
            return SUCCESS;
            }
          }
	}

        return -1;
    }
};
class Queen : public Piece {
protected:
    friend PieceFactory<Queen>;
    Queen(Player owner, int id) : Piece(owner , id) {}
public:
    // This method will have piece-specific logic for checking valid moves
    // It may also call the generic Piece::validMove for common logic
    int validMove(Position start, Position end,
        const Board& board) const override {
        Piece* startpiece = board.getPiece(start);
        Piece* endpiece = board.getPiece(end);
        unsigned int a = start.y + 1;
        unsigned int b = start.y - 1;
        unsigned int c = start.x + 1;
        unsigned int d = start.x - 1;
        if(endpiece != nullptr && startpiece->owner() == endpiece->owner()){
          return -2;
        }
	else if(endpiece == nullptr || startpiece->owner() != endpiece->owner()){
          if((start.x == end.x)&&((end.y - start.y) < 8)){
            if(end.y > start.y){
              for(;a < end.y; ++a){
                Piece* betweenpiece = board.getPiece(Position(start.x,a));
                if(betweenpiece != nullptr){
                  return -2;
                }
              }
              return SUCCESS;
            }
          }
          //MOVING DOWN                                                                                                                                                                                  
          if((start.x == end.x)&&((start.y - end.y) < 8)){
            if(start.y > end.y){
              for(;b > end.y; --b){
                Piece* betweenpiece = board.getPiece(Position(start.x,b));
                if(betweenpiece != nullptr){
                  return -2;
                }
              }
              return SUCCESS;
            }
          }
          //MOVING RIGHT                                                                                                                                                                                  
          if((start.y == end.y)&&((end.x - start.x) < 8)){
            if(end.x > start.x){
              for(;c < end.x; ++c){
                Piece* betweenpiece = board.getPiece(Position(c, start.y));
                if(betweenpiece != nullptr){
                  return -2;
                }
              }
              return SUCCESS;
            }
          }
          //MOVING LEFT
	  if((start.y == end.y)&&((start.x - end.x) < 8)){
            if(start.x > end.x){
              for(;d > end.x; --d){
                Piece* betweenpiece = board.getPiece(Position(d, start.y));
                if(betweenpiece != nullptr){
                  return -2;
                }
              }
              return SUCCESS;
            }
          }
	  //TOP RIGHT DIAGONALS                                                                                                                                                                           
          unsigned int xcoord1 = start.x + 1;
          unsigned int ycoord1 = start.y + 1;
          unsigned int xcoord2 = start.x - 1;
          unsigned int ycoord2 = start.y - 1;
          if((((int)end.x - start.x) > 0) &&(((int)end.y - start.y) > 0)){
            if((end.x - start.x) == (end.y - start.y)){
              while((end.x > xcoord1)&&(end.y > ycoord1)){
                Piece* betweenpiece = board.getPiece(Position(xcoord1, ycoord1));
                if(betweenpiece != nullptr){
                  return -2;
                }
                ++xcoord1;
                ++ycoord1;
              }
            return SUCCESS;
            }
          }
          //TOP LEFT DIAGONALS                                                                                                                                                                            
          if((((int)start.x - end.x) > 0) &&(((int)end.y - start.y) > 0)){
            if((start.x - end.x) == (end.y - start.y)){
              while((end.x < xcoord2)&&(end.y > ycoord1)){
                Piece* betweenpiece = board.getPiece(Position(xcoord2, ycoord1));
                if(betweenpiece != nullptr){
                  return -2;
                }
                --xcoord1;
                ++ycoord1;
              }
            return SUCCESS;
            }
          }

          //BOTTOM RIGHT DIAGONALS                                                                                                                                                                        
          if((((int)end.x - start.x) > 0) &&(((int)start.y - end.y) > 0)){
            if((end.x - start.x) == (start.y - end.y)){
              while((end.x > xcoord1)&&(end.y < ycoord2)){
                Piece* betweenpiece = board.getPiece(Position(xcoord1, ycoord2));
                if(betweenpiece != nullptr){
                  return -2;
                }
                ++xcoord1;
                --ycoord1;
              }
            return SUCCESS;
            }
          }
          //BOTTOM LEFT DIAGONALS
	  if((((int)start.x - end.x) > 0) &&(((int)start.y - end.y) > 0)){
            if((start.x - end.x) == (start.y - end.y)){
              while((end.x < xcoord2)&&(end.y < ycoord2)){
                Piece* betweenpiece = board.getPiece(Position(xcoord1, ycoord2));
                if(betweenpiece != nullptr){
                  return -2;
                }
                --xcoord1;
                --ycoord1;
              }
            return SUCCESS;
            }
          }
        }                             
        return -1;
    }
};
class King : public Piece {
protected:
    friend PieceFactory<King>;
    King(Player owner, int id) : Piece(owner, id) {}
public:
    // This method will have piece-specific logic for checking valid moves
    // It may also call the generic Piece::validMove for common logic
    int validMove(Position start, Position end,
        const Board& board) const override {
        Piece* startpiece = board.getPiece(start);
        Piece* endpiece = board.getPiece(end);
        if(endpiece != nullptr && startpiece->owner() == endpiece->owner()){
          return -2;
        }
	//VERTICAL MOVING
	else if(endpiece == nullptr || startpiece->owner() != endpiece->owner()){
	  if((end.x - start.x) == 0){
	    if((end.y - start.y) == 1){
	      return SUCCESS;
	    }
	    else if((start.y - end.y) == 1){
	      return SUCCESS;
	    }
	  }
	  //HORIZONTAL MOVING
	  else if((end.y - start.y) == 0){
	    if((end.x - start.x) == 1){
	      return SUCCESS;
	    }
	    else if((start.x - end.x) == 1){
	      return SUCCESS;
	    }
	  }
	  //DIAGONAL MOVING TOP CORNERS
	  else if((end.y - start.y) == 1){
	    if((end.x - start.x) == 1){
	      return SUCCESS;
	    }
	    else if((start.x - end.x) == 1){
	      return SUCCESS;
	    }
	  }
	  //DIAGONAL MOVING BOTTOM CORNERS
	  else if((start.y - end.y) == 1){
	    if((end.x - start.x) == 1){
              return SUCCESS;
            }
	    else if((start.x - end.x) == 1){
	      return SUCCESS;
	    }
	  }
	}
        return -1;
    }
};

class ChessGame : public Board {
public:
    ChessGame() : Board(8, 8) {
        // Add all factories needed to create Piece subclasses
        addFactory(new PieceFactory<Pawn>(PAWN_ENUM));
        addFactory(new PieceFactory<Rook>(ROOK_ENUM));
        addFactory(new PieceFactory<Knight>(KNIGHT_ENUM));
        addFactory(new PieceFactory<Bishop>(BISHOP_ENUM));
        addFactory(new PieceFactory<Queen>(QUEEN_ENUM));
        addFactory(new PieceFactory<King>(KING_ENUM));
	addFactory(new PieceFactory<MysteryPiece>(10));
    }
    
    // Setup the chess board with its initial pieces
    virtual void setupBoard();

    // Whether the chess game is over
    virtual bool gameOver() const override { return false; }

    // Perform a move from the start Position to the end Position
    // The method returns an integer with the status
    // >= 0 is SUCCESS, < 0 is failure
    virtual int makeMove(Position start, Position end) override;
    //run the game
    virtual void run();
    //print the board
    virtual void printBoard();
    //Returns true if the person whose turn it is, is in check.
    virtual int inCheck();
    //returns true of the player is moving themself into check.
    virtual int moveToCheck(Position start, Position end);
    //method to load a chess game
    virtual void loadGame();

    virtual void saveGame();

    virtual int stalemate();
}; 

#endif
