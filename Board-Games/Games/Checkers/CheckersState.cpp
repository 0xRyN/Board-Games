#include "CheckersState.hpp"

#include <Board-Games/Games/Checkers/Pieces/Pawn/CheckersPawn.hpp>
#include "Board-Games/Games/Checkers/Pieces/Pawn/CheckersQueen.hpp"

CheckersState::CheckersState(int boardSize, Player* firstPlayer,
                             Player* secondPlayer)
    : GameState(boardSize) {
    this->initializeGame();
}

void CheckersState::initializeGame() {
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            if (board[i][j].getIsDark() && j < 4) {
                board[i][j].setPiece(new CheckersPawn(i, j, Color::White));
            } else if (board[i][j].getIsDark() && j > 5) {
                board[i][j].setPiece(new CheckersPawn(i, j, Color::Black));
            } else {
                board[i][j].removePiece();
            }
        }
    }

    // Compute available moves for the first player
    computeAvailableMoves();
}

void CheckersState::promotePawn(int x, int y) {
    CheckersPawn* Pawn = dynamic_cast<CheckersPawn*>(board[x][y].getPiece());
    delete Pawn;
    board[x][y].setPiece(new CheckersQueen(x, y, board[x][y].getPiece()->getColor()));
}
