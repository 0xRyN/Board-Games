#include "CheckersQueen.hpp"

CheckersQueen::CheckersQueen(int posX, int posY, Color pieceColor) 
    : Piece(posX, posY, pieceColor) {
    texturePath = (pieceColor == Color::White)
                      ? "assets/Pieces/Checkers/Queen/light.png"
                      : "assets/Pieces/Checkers/Queen/dark.png";
}

bool CheckersQueen::canMove(GameState& state, int toX, int toY) const {
    // Movement rules for queen checkers :
    // 1. Can move diagonally any number of squares
    // If statements are separated like this for optimization (short-circuiting)

    // Check if the queen is moving diagonally
    if (abs(toX - x) != abs(toY - y)) {
        return false;
    }

    // Check if there is a piece in the destination square
    if (state.getTileAt(toX, toY).getPiece() != nullptr) {
        return false;
    }

    // Check if there are any pieces in the way
    int xDir = (toX - x) / abs(toX - x);
    int yDir = (toY - y) / abs(toY - y);
    for (int i = 1; i < abs(toX - x); i++) {
        if (state.getTileAt(x + i * xDir, y + i * yDir).getPiece() != nullptr) {
            return false;
        }
    }
    return true;
}




