#include "CheckersState.hpp"

#include "Board-Games/Games/Checkers/Pieces/Pawn/CheckersQueen.hpp"
#include <Board-Games/Games/Checkers/Pieces/Pawn/CheckersPawn.hpp>

CheckersState::CheckersState(int boardSize, Player* firstPlayer,
                             Player* secondPlayer) 
    : GameState(boardSize), captureLeft(0) {
    this->initializeGame();
}

void CheckersState::initializeGame() {
    std::cout << "Initializing Checkers game..." << std::endl;
    GameState::initializeGame();

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
            if (board[i][j].getIsDark() && j < 3) {
                board[i][j].setPiece(new CheckersPawn(i, j, Color::White));
            } else if (board[i][j].getIsDark() && j > 4) {
                board[i][j].setPiece(new CheckersPawn(i, j, Color::Black));
            } else {
                board[i][j].removePiece();
            }
        }
    }

    // Compute available moves for the first player
    computeAvailableMoves();
}

void CheckersState::startCaptureSequence(int nbCaptures) {
    captureLeft = nbCaptures;
}

void CheckersState::decreaseCaptureLeft() {
    captureLeft--;
}

bool CheckersState::isCaptureSequenceInProgress() const {
    return captureLeft > 0;
}

void CheckersState::computeAvailableMoves() {
    GameState::computeAvailableMoves();

}
