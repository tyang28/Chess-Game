#undef FOR_RELEASE

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>
#include "Game.h"
#include "Chess.h"
#include "Prompts.h"

int pawntest(const Board& chess){
    Piece* startpiece = chess.getPiece(Position(1,3));
    Piece* startpiece2 = chess.getPiece(Position(2,1));
    Piece* startpiece3 = chess.getPiece(Position(6,2));
    int final;
    //block by own piece
    int movereturn = startpiece->validMove(Position(1,3),Position(1,4), chess);
    //forwards 2
    int movereturn2 = startpiece2->validMove(Position(2,1),Position(2,3), chess);
    //forwards 1
    int movereturn3 = startpiece2->validMove(Position(2,1),Position(2,2), chess);
    //Top right diagonal capture
    int movereturn4 = startpiece3->validMove(Position(6,2),Position(7,3), chess);
    //Top left diagonal capture
    int movereturn5 = startpiece3->validMove(Position(6,2),Position(5,3), chess);
    if(movereturn == -2){
      final = 0;
    }
    else{
      final = -1;
    }

    if(movereturn2 == 1){
      final = 0;
    }
    else{
      final = -1;
    }
    if(movereturn3 == 1){
      final = 0;
    }
    else{
      final = -1;
    }
    if(movereturn4 == 1){
      final = 0;
    }
    else{
      final = -1;
    }
    if(movereturn5 == 1){
      final = 0;
    }
    else{
      final = -1;
    }
    return final;

}
int rooktest(const Board& chess){
  Piece* startpiece = chess.getPiece(Position(2,1));
  Piece* startpiece2 = chess.getPiece(Position(2,6));
  int final;
  //block by own piece                                                                                                                                                                                  
  int movereturn = startpiece->validMove(Position(2,1),Position(2,2), chess);
  //move right + capture
  int movereturn1 = startpiece2->validMove(Position(2,6),Position(4,6), chess);
  //move left + capture
  int movereturn2 = startpiece2->validMove(Position(2,6),Position(0,6), chess);
  //move up + capture
  int movereturn3 = startpiece2->validMove(Position(2,6),Position(2,7), chess);
  //move down + capture
  int movereturn4 = startpiece2->validMove(Position(2,6),Position(2,4), chess);
  
  if(movereturn == -2){
    final = 0;
  }
  else{
    final = -1;
  }
  if(movereturn1 == 1){
    final = 0;
  }
  else{
    final = -1;
  }
  if(movereturn2 == 1){
    final = 0;
  }
  else{
    final = -1;
  }
  if(movereturn3 == 1){
    final = 0;
  }
  else{
    final = -1;
  }
  if(movereturn4 == 1){
    final = 0;
  }
  else{
    final = -1;
  }

  return final;
}
int knighttest(const Board& chess){
  Piece* startpiece = chess.getPiece(Position(4,4));
  Piece* startpiece2 = chess.getPiece(Position(7,4));
  int final;
  //1 right 2 up + capture                                                                                                                                                                                   
  int movereturn = startpiece->validMove(Position(4,4),Position(5,6), chess);
  //1 left 2 up                                                                                                                                                                                
  int movereturn1 = startpiece->validMove(Position(4,4),Position(3,6), chess);
  //2 right 1 up                                                                                                                                                                                  
  int movereturn2 = startpiece->validMove(Position(4,4),Position(6,5), chess);
  //2 left 1 up                                                                                                                                                                                   
  int movereturn3 = startpiece->validMove(Position(4,4),Position(2,5), chess);
  //2 right 1 down                                                                                                                                                                                  
  int movereturn4 = startpiece->validMove(Position(4,4),Position(6,3), chess);
  //2 left 1 down                                                                                                                                                                                       
  int movereturn6 = startpiece->validMove(Position(4,4),Position(2,3), chess);
  //1 right 2 down                                                                                                                                                                                       
  int movereturn7 = startpiece->validMove(Position(4,4),Position(5,2), chess);
  //1 left 2 down                                                                                                                                                                                       
  int movereturn8 = startpiece->validMove(Position(4,4),Position(3,2), chess);
  //blocked by own piece
  int movereturn5 = startpiece2->validMove(Position(7,4),Position(6,2), chess);

  if(movereturn5 == -2){
    final = 0;
  }
  else{
    final = -1;
  }
  if(movereturn == 1){
    final = 0;
  }
  else{
    final = -1;
  }
  if(movereturn1 == 1){
    final = 0;
  }
  else{
    final = -1;
  }
  if(movereturn2 == 1){
    final = 0;
  }
  else{
    final = -1;
  }
  if(movereturn3 == 1){
    final = 0;
  }
  else{
    final = -1;
  }
  if(movereturn4 == 1){
    final = 0;
  }
  else{
    final = -1;
  }
  if(movereturn6 == 1){
    final = 0;
  }
  else{
    final = -1;
  }
  if(movereturn7 == 1){
    final = 0;
  }
  else{
    final = -1;
  }
  if(movereturn8 == 1){
    final = 0;
  }
  else{
    final = -1;
  }




  return final;

}
int bishoptest(const Board& chess){
  Piece* startpiece = chess.getPiece(Position(3,5));
  Piece* startpiece2 = chess.getPiece(Position(2,1));
  int final;
  
  //Top Right                                                                                                                                                                                        
  int movereturn = startpiece->validMove(Position(3,5),Position(5,7), chess);
  // Top left                                                                                                                                                                                          
  int movereturn1 = startpiece->validMove(Position(3,5),Position(5,3), chess);
  //Bottom Right                                                                                                                                                                                         
  int movereturn2 = startpiece->validMove(Position(3,5),Position(1,3), chess);
  //Bottom left  
  int movereturn3 = startpiece->validMove(Position(3,5),Position(1,7), chess);
  //blocked by own piece                                                                                                                                                                                
  int movereturn4 = startpiece2->validMove(Position(2,1),Position(3,2),chess);                                                                                                                             if(movereturn4 == -2){
    final = 0;
  }
  else{
    final = -1;
  }
  if(movereturn == 1){
    final = 0;
  }
  else{
    final = -1;
  }
  if(movereturn1 == 1){
    final = 0;
  }
  else{
    final = -1;
  }
  if(movereturn2 == 1){
    final = 0;
  }
  else{
    final = -1;
  }
  if(movereturn3 == 1){
    final = 0;
  }
  else{
    final = -1;
  }                                                                                                                                                                                                                                                                                                                      
  return final;
}
int queentest(const Board& chess){
  Piece* startpiece = chess.getPiece(Position(2,5));
  Piece* startpiece2 = chess.getPiece(Position(2,1));
  int final;
  //Top Right + capture                                                                                                                                                                                                                                                                                                                                                         
  int movereturn = startpiece->validMove(Position(2,5),Position(4,7), chess);
  //Top + capture                                                                                                                                                                                         
  int movereturn1 = startpiece->validMove(Position(2,5),Position(2,7), chess);
  //Top left + capture                                                                                                                                                                                   
  int movereturn2 = startpiece->validMove(Position(2,5),Position(0,7), chess);
  //Right + capture                                                                                                                                                                                    
  int movereturn3 = startpiece->validMove(Position(2,5),Position(4,5), chess);
  //Left + capture                                                                                                                                                                                       
  int movereturn4 = startpiece->validMove(Position(2,5),Position(0,5), chess);
  //Bottom Right + capture                                                                                                                                                                             
  int movereturn5 = startpiece->validMove(Position(2,5),Position(4,3), chess);
  //Bottom Left + capture                                                                                                                                                                               
  int movereturn6 = startpiece->validMove(Position(2,5),Position(0,3), chess);
  //Bottom + capture                                                                                                                                                                                 
  int movereturn7 = startpiece->validMove(Position(2,5),Position(2,3), chess);
  //blocked by own piece                                                                                                                                                                                 
  int movereturn8 = startpiece2->validMove(Position(2,1),Position(2,3), chess);
  if(movereturn8 == -2){
    final = 0;
  }
  else{
    final = -1;
  }
  if(movereturn == 1){
    final = 0;
  }
  else{
    final = -1;
  }              
  if(movereturn1 == 1){
    final = 0;
  }
  else{
    final = -1;
  }
  if(movereturn2 == 1){
    final = 0;
  }
  else{
    final = -1;
  }
  if(movereturn3 == 1){
    final = 0;
  }
  else{
    final = -1;
  }
  if(movereturn4 == 1){
    final = 0;
  }
  else{
    final = -1;
  }
  if(movereturn5 == 1){
    final = 0;
  }
  else{
    final = -1;
  }
  if(movereturn6 == 1){
    final = 0;
  }
  else{
    final = -1;
  }
  if(movereturn7 == 1){
    final = 0;
  }
  else{
    final = -1;
  }
  return final;
}
int kingtest(const Board& chess){
  Piece* startpiece = chess.getPiece(Position(2,5));
  Piece* startpiece2 = chess.getPiece(Position(2,3));
  int final;
  //Top Right + capture                                                                                                                                                                               
                                                                                                                                                                                                        
  int movereturn = startpiece->validMove(Position(2,5),Position(3,6), chess);
  //Top + capture                                                                                                                                                                                                                                                                                                                                                                                          
  int movereturn1 = startpiece->validMove(Position(2,5),Position(2,6), chess);
  //Top left + capture                                                                                                                                                                                   
  int movereturn2 = startpiece->validMove(Position(2,5),Position(1,6), chess);
  //Right + capture                                                                                                                                                                                       
  int movereturn3 = startpiece->validMove(Position(2,5),Position(3,5), chess);
  //Left + capture                                                                                                                                                                                       
  int movereturn4 = startpiece->validMove(Position(2,5),Position(1,5), chess);
  //Bottom Right + capture                                                                                                                                                                                
  int movereturn5 = startpiece->validMove(Position(2,5),Position(3,4), chess);
  //Bottom Left + capture                                                                                                                                                                                 
  int movereturn6 = startpiece->validMove(Position(2,5),Position(1,4), chess);
  //Bottom + capture                                                                                                                                                                                      
  int movereturn7 = startpiece->validMove(Position(2,5),Position(2,4), chess);
  //blocked by own piece                                                                                                                                                                                 
  int movereturn8 = startpiece2->validMove(Position(2,3),Position(2,4), chess);
  if(movereturn8 == -2){
    final = 0;
  }
  else{
    final = -1;
  }
  if(movereturn == 1){
    final = 0;
  }
  else{
    final = -1;
  }
  if(movereturn1 == 1){
    final = 0;
  }
  else{
    final = -1;
  }
  if(movereturn2 == 1){
    final = 0;
  }
  else{
    final = -1;
  }
  if(movereturn3 == 1){
    final = 0;
  }
  else{
    final = -1;
  }
  if(movereturn4 == 1){
    final = 0;
  }
  else{
    final = -1;
  }
  if(movereturn5 == 1){
    final = 0;
  }
  else{
    final = -1;
  }
  if(movereturn6 == 1){
    final = 0;
  }
  else{
    final = -1;
  }
  if(movereturn7 == 1){
    final = 0;
  }
  else{
    final = -1;
  }
  return final;
}
int main() {
    ChessGame chess;
    std::cout << "Enter input file twice" << std::endl;
    std::string input;
    std::cin >> input;
    chess.loadGame();
    if(input == "pawn.txt"){
      if(pawntest(chess) == 0){
        std::cout << "Pawn test passes!" << std::endl;
      }
      else{
	std::cout << "Pawn test fails!" << std::endl;
      }
    }
    
    if(input == "rook.txt"){
      if(rooktest(chess) == 0){
         std::cout << "Rook test passes!" << std::endl;
      }
      else{
        std::cout << "Rook test fails!" << std::endl;
      }
    }
    if(input == "knight.txt"){
      if(knighttest(chess) == 0){
	std::cout << "knight test passes!" << std::endl;
      }
      else{
        std::cout << "Knight test fails!" << std::endl;
      }
    }
    if(input == "bishop.txt"){
      if(bishoptest(chess) == 0){
        std::cout << "bishop test passes!" << std::endl;
      }
      else{
        std::cout << "bishop test fails!" << std::endl;
      }
    }
    if(input == "queen.txt"){
      if(queentest(chess) == 0){
        std::cout << "queen test passes!" << std::endl;
      }
      else{
        std::cout << "queen test fails!" << std::endl;
      }
    }
    if(input == "king.txt"){
      if(kingtest(chess) == 0){
        std::cout << "king test passes!" << std::endl;
      }
      else{
        std::cout << "king test fails!" << std::endl;
      }
    } 
   
    
    
}
