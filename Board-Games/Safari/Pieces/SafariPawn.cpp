#include "SafariPawn.hpp"

SafariPawn::SafariPawn(int posX, int posY, Color pieceColor) : Piece(posX, posY, pieceColor) {
    if (pieceColor == Color::White) {
        texturePath = "assets/white_pawn.png";
    } else {
        texturePath = "assets/black_pawn.png";
    }
}

bool SafariPawn::canMove(GameState& state, int toX, int toY) const {
    // Implementation of canMove function
    if (toX < 0 || toX > 7 || toY < 0 || toY > 7) {
        return false;
    }
    if (state.getTileAt(toX, toY).getPiece() != nullptr) {
        return false;
    }
    if (toX == x && toY == y) {
        return false;
    }
    if (abs(toX - x) > 1 || abs(toY - y) > 1) {
        return false;
    }
    return true;
}

bool SafariPawn::isPathClear(GameState& state, int toX, int toY) const {
    
    
}