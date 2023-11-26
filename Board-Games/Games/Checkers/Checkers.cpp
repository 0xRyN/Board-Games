
#include "Checkers.hpp"
#include <Board-Games/Games/Checkers/Pieces/Pawn/CheckersPawn.hpp>

Checkers::Checkers() : BoardGame(8) {
    // Implementation of Checkers constructor
    this->loadTextures();
    this->initializeGame();
}

void Checkers::initializeGame() {
    // Implementation of initializeGame function
    for (int i = 0; i < 8; i++) {
        this->board[1][i].setPiece(new CheckersPawn(i, 1, Color::White));
        this->board[6][i].setPiece(new CheckersPawn(i, 6, Color::Black));
    }
}

void Checkers::loadTextures() {
    // Implementation of loadTextures function
    std::string textures[] = {
        "assets/Pieces/Checkers/Pawn/white.png",
        "assets/Pieces/Checkers/Pawn/black.png",

    };

    for (std::string texture : textures) {
        sf::Texture tex;
        tex.loadFromFile(texture);
        this->textures[texture] = tex;
    }
}

bool Checkers::movePiece(int fromX, int fromY, int toX, int toY) {
    // Implementation of movePiece function
    return false;
}
