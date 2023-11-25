#ifndef TILE_HPP
#define TILE_HPP

#include <Board-Games/Piece.hpp>

class Tile {
  private:
    Piece* piece;

  public:
    Tile(bool dark);
    bool isDark;
    void setPiece(Piece* newPiece);
    void removePiece();
    Piece* getPiece() const;
    bool hasPiece() const;
};

#endif