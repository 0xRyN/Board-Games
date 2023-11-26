#include "Tile.hpp"

Tile::Tile(bool dark) : piece(nullptr), isDark(dark) {
}

bool Tile::getIsDark() const {
    return isDark;
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
