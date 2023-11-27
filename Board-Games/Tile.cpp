#include "Tile.hpp"

Tile::Tile(bool dark) : piece(nullptr), isDark(dark), x(0), y(0) {
    this->texturePath =
        (dark) ? "assets/Tiles/dark.png" : "assets/Tiles/light.png";
}

bool Tile::getIsDark() const {
    return isDark;
}

std::string Tile::getTexturePath() const {
    return texturePath;
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

int Tile::getX() const {
    return x;
}

int Tile::getY() const {
    return y;
}
