#include "Piece.hpp"

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
