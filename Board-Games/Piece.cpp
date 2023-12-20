#include "Piece.hpp"
#include <Board-Games/common.hpp>

bool Piece::isPathClear(GameState& state, int fromX, int fromY, int toX,
                        int toY) const {

    if (fromX == toX && fromY == toY) {
        return true;
    }

    int x = fromX, y = fromY;
    int dx = toX - fromX, dy = toY - fromY;
    int steps = std::max(std::abs(dx), std::abs(dy));
    dx /= steps;
    dy /= steps;

    for (int i = 0; i < steps; ++i) {
        x += dx;
        y += dy;
        if (state.getTileAt(x, y).hasPiece()) {
            return false;
        }
    }

    return true;
}

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
    // If the path is not clear, it's a capture
    if (!isPathClear(state, x, y, toX, toY)) {
        return canCapture(state, toX, toY);
    }

    return canMove(state, toX, toY);
}
