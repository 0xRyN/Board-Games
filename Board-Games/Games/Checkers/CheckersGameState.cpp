#include "CheckersGameState.hpp"
#include "CheckersPawn.hpp"


void CheckersGameState::initializeGame() {
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
}

void CheckersGameState::creatBoard() {
    for (int i = 0; i < boardSize; i++) {
        std::vector<Tile> row;
        for (int j = 0; j < boardSize; j++) {
            row.push_back(Tile(i, j, (i + j) % 2 == 0));
        }
        board.push_back(row);
    }
}


