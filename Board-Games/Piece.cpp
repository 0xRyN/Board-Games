#include "Piece.hpp"
#include <Board-Games/common.hpp>


Piece::Piece(int posX, int posY, Color pieceColor)
    : x(posX), y(posY), color(pieceColor) {
}

int Piece::getX() const {
    return x;
}

int Piece::getY() const {
    return y;
}

void Piece::setPosition(int posX, int posY) {
    x = posX;
    y = posY;
}

Color Piece::getColor() const {
    return color;
}

std::string Piece::getTexturePath() const {
    return texturePath;
}

bool Piece::isValidMove(GameState& state, int toX, int toY) const {
    // Check if the destination is out of bounds
    if (toX < 0 || toX >= state.getBoardSize() || toY < 0 ||
        toY >= state.getBoardSize()) {
        return false;
    }
    // If the path is not clear, it's a capture
    return canCapture(state, toX, toY) || canMove(state, toX, toY);
}
