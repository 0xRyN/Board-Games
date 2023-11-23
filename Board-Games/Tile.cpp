#include "Tile.hpp"

Tile::Tile(bool dark) : isDark(dark), piece(nullptr) {
}

void Tile::setPiece(Piece* newPiece) {
    piece = newPiece;
}

void Tile::removePiece() {
    if (piece != nullptr) {
        delete piece;
        piece = nullptr;
    }
}

Piece* Tile::getPiece() const {
    return piece;
}

bool Tile::hasPiece() const {
    return piece != nullptr;
}
