#ifndef TILE_HPP
#define TILE_HPP

#include <Board-Games/Piece.hpp>

class Tile {
  private:
    Piece* piece;
    bool isDark;
    std::string texturePath;
    int x, y;

  public:
    Tile(bool dark, int x, int y);
    bool getIsDark() const;
    std::string getTexturePath() const;
    void setPiece(Piece* newPiece);
    void removePiece();
    Piece* getPiece() const;
    bool hasPiece() const;
    int getX() const;
    int getY() const;
};

#endif