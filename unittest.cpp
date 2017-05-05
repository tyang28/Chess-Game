#undef FOR_RELEASE

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>
#include "Game.h"
#include "Chess.h"
#include "Prompts.h"

int main() {
    ChessGame chess;
    chess.loadGame();
    Piece* startpiece = chess.getPiece(Position(1,3));
    Piece* endpiece = chess.getPiece(Position(1,4));
    Piece* startpiece2 = chess.getPiece(Position(2,1));
    Piece* endpiece2 = chess.getPiece(Position(2,3));
    int cresponse = 0;
    int final = -1;
    int movereturn = startpiece->validMove(Position(1,3),Position(1,4), chess);
    int movereturn2 = startpiece2->validMove(Position(2,1),Position(2,3), chess);
    
    if(movereturn == -2){
      final = 0;
    }
    else{
      final = -1;
    }
    if(endpiece2->owner() == 2){
      if(startpiece2->owner() == 0){
	if(movereturn2 == 0){
	  final = 0;
	}
      }
    }
    else{
      final = -1;
    }

    
    
}
