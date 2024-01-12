#include "CheckersState.hpp"

#include "Board-Games/Games/Checkers/Pieces/Pawn/CheckersQueen.hpp"
#include <Board-Games/Games/Checkers/Pieces/Pawn/CheckersPawn.hpp>
#include "Board-Games/Games/Checkers/Pieces/Pawn/CheckersQueen.hpp"

CheckersState::CheckersState(int boardSize, Player* firstPlayer,
                             Player* secondPlayer) 
    : GameState(boardSize), captureLeft(0) {
    this->initializeGame();
}

void CheckersState::initializeGame() {

    bool DEBUG = 0;
    if (DEBUG) {
        board[9][6].setPiece(new CheckersQueen(9, 6, Color::White));

        // Add white pawns in these positions
        /*
        (8, 5)
        (5, 4)
        (3, 8)
        (6, 7)
        */
        board[8][5].setPiece(new CheckersPawn(8, 5, Color::Black));
        board[6][5].setPiece(new CheckersPawn(5, 4, Color::Black));
        board[5][4].setPiece(new CheckersPawn(5, 4, Color::Black));
        board[3][8].setPiece(new CheckersPawn(3, 8, Color::Black));
        board[6][7].setPiece(new CheckersPawn(6, 7, Color::Black));

        computeAvailableMoves();
        return;
    }

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
