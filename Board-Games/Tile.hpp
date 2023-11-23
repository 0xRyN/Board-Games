#ifndef TILE_HPP
#define TILE_HPP

#include <Board-Games/Piece.hpp>

class Tile {
  public:
    bool isDark;
    Piece* piece;
    Tile(bool dark);

    void setPiece(Piece* newPiece);
    void removePiece();
    Piece* getPiece() const;
    bool hasPiece() const;
};

#endif