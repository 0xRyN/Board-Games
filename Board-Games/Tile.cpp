#include "Tile.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

Tile::Tile(bool dark, int x, int y) : piece(nullptr), isDark(dark), x(x), y(y) {
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

bool Tile::isReachable() const {
    return state == TileState::Reachable;
}

void Tile::setReachable(bool reachable) {
    state = (reachable) ? TileState::Reachable : TileState::Normal;
}
