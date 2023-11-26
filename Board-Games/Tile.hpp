#ifndef TILE_HPP
#define TILE_HPP

#include <Board-Games/Piece.hpp>

class Tile {
  private:
    Piece* piece;
    bool isDark;

  public:
    Tile(bool dark);
    bool getIsDark() const;
    void setPiece(Piece* newPiece);
    void removePiece();
    Piece* getPiece() const;
    bool hasPiece() const;
};

#endif