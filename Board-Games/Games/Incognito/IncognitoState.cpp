#include "IncognitoState.hpp"
#include <Board-Games/Games/Incognito/Pieces/IncognitoPawn.hpp>

IncognitoState::IncognitoState(int boardSize, Player* firstPlayer,
                               Player* secondPlayer)
    : GameState(boardSize) {
    this->initializeGame();
}

void IncognitoState::initializeGame() {
    //initialize the board with the pieces on the following positions for a 5x5 board
    //(2,0)->white (3,0)->white
    //(3,1)->white (4,1)->white 
    //(0,2)->black (4,2)->white
    //(0,3)->black (1,3)->black
    //(1,4)->black (2,4)->black

    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            if ((i == 2 && j == 0) || (i == 3 && j == 0) || (i == 3 && j == 1) || (i == 4 && j == 1) || (i == 4 && j == 2) ) {
                board[i][j].setPiece(new IncognitoPawn(i, j, Color::White));
            }
            else if ((i == 0 && j == 2) || (i == 0 && j == 3) || (i == 1 && j == 3) || (i == 1 && j == 4) || (i == 2 && j == 4)) {
                board[i][j].setPiece(new IncognitoPawn(i, j, Color::Black));
            }
            else {
                board[i][j].removePiece();
            }
        }
    }

    // Compute available moves for the first player
    computeAvailableMoves();

    
}
