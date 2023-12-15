#ifndef TILE_HPP
#define TILE_HPP

#include "Piece.hpp"

enum class TileState {
    Normal,
    Reachable,
};
class Tile {
  private:
    Piece* piece;
    bool isDark;
    std::string texturePath;
    int x, y;
    TileState state;

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
    bool isReachable() const;
    void setReachable(bool reachable);
};

#endif