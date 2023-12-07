
#include "Checkers.hpp"
#include <Board-Games/Games/Checkers/Pieces/Pawn/CheckersPawn.hpp>

int CHECKERS_BOARD_SIZE = 10;
Checkers::Checkers() : BoardGame(CHECKERS_BOARD_SIZE) {
    // Implementation of Checkers constructor
    this->loadTextures();
    this->initializeGame();
}

void Checkers::initializeGame() {
    // Implementation of initializeGame function
    for (int i = 0; i < CHECKERS_BOARD_SIZE; i++) {
        for (int j = 0; j < CHECKERS_BOARD_SIZE; j++) {
            if (board[i][j].getIsDark() && j < 4) {
                board[i][j].setPiece(new CheckersPawn(i, j, Color::White));
            } else if (board[i][j].getIsDark() && j > 5) {
                board[i][j].setPiece(new CheckersPawn(i, j, Color::Black));
            } else {
                board[i][j].removePiece();
            }
        }
    }
}

void Checkers::loadTextures() {
    // Implementation of loadTextures function
    BoardGame::loadTextures();
    std::string textures[] = {
        "assets/Pieces/Checkers/Pawn/white.png",
        "assets/Pieces/Checkers/Pawn/black.png",

    };

    for (std::string texture : textures) {
        sf::Texture tex;
        tex.loadFromFile(texture);
        tex.setSmooth(true);
        this->textures[texture] = tex;
    }
}
