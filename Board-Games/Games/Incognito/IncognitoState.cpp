#include "IncognitoState.hpp"
#include <Board-Games/Games/Incognito/Pieces/IncognitoPawn.hpp>

IncognitoState::IncognitoState(int boardSize, Player* firstPlayer,
                               Player* secondPlayer)
    : GameState(boardSize) {
    this->initializeGame();
}

void IncognitoState::initializeGame() {

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
    putRandomSpies();
    computeAvailableMoves();

    
}

void IncognitoState::putRandomSpies() {
    //transform a random pawn into a spy for each player
    int x = rand() % 5;
    int y = rand() % 5;
    IncognitoPawn* Pawn = dynamic_cast<IncognitoPawn*>(board[x][y].getPiece());
    Pawn->setIsASpy(true);
    x = rand() % 5;
    y = rand() % 5;
    Pawn = dynamic_cast<IncognitoPawn*>(board[x][y].getPiece());
    Pawn->setIsASpy(true);
}