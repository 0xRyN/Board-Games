#include "CheckersQueen.hpp"

CheckersQueen::CheckersQueen(int posX, int posY, Color pieceColor) 
    : Piece(posX, posY, pieceColor) {
    texturePath = (pieceColor == Color::White)
                      ? "assets/Pieces/Checkers/Queen/light.png"
                      : "assets/Pieces/Checkers/Queen/dark.png";
}

bool CheckersQueen::canMove(GameState& state, int toX, int toY) const {
    //Check if the queen is moving diagonally
    if (abs(toX - x) != abs(toY - y)) {
        return false;
    }

    // Check if there is a piece in the destination square
    if (state.getTileAt(toX, toY).getPiece() != nullptr) {
        return false;
    }

    return true;
}


bool CheckersQueen::canCapture(GameState& state, int toX, int toY) const {
        //check if there is a piece adjacent to the destination square
    int xDir = (toX - x) / abs(toX - x);
    int yDir = (toY - y) / abs(toY - y);
    if (state.getTileAt(toX - xDir, toY - yDir).getPiece() == nullptr) {
        return false;
    }
    return true;
}





