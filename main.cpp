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
    Prompts prompt = Prompts();
    int input;
    prompt.menu();

    while(1){
        scanf(" %d", &input);
        if (input == 2) {
            prompt.loadGame();
            chess.loadGame();
            chess.run();
            prompt.gameOver();
            break;
        } else if( input != 1) {
            prompt.menu();
        } else {
           break;
        }
    }
    if (input == 1) {
        chess.setupBoard();
        chess.run();
        prompt.gameOver();
    }
}

