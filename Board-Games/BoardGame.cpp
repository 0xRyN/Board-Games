#include "BoardGame.hpp"

BoardGame::BoardGame(int boardSize)
    : size(boardSize), currentPlayer(Player::Player1) {
    for (int i = 0; i < size; ++i) {
        std::vector<Tile> row;
        for (int j = 0; j < size; ++j) {
            row.push_back(Tile((i + j) % 2 == 0));
        }
        board.push_back(row);
    }
}

int BoardGame::getBoardSize() const {
    return size;
}

void BoardGame::displayBoard() {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            std::cout << (board[i][j].isDarkTile() ? "X " : "O ");
        }
        std::cout << std::endl;
    }
}

void BoardGame::changePlayer() {
    currentPlayer =
        (currentPlayer == Player::Player1) ? Player::Player2 : Player::Player1;
}

bool BoardGame::movePiece(int fromX, int fromY, int toX, int toY) {
    return false;
}
