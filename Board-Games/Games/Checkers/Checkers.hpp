#ifndef CHECKERS_HPP
#define CHECKERS_HPP

#include <Board-Games/BoardGame.hpp>
#include <Board-Games/Piece.hpp>

class Checkers : public BoardGame {
  public:
    Checkers();
    void initializeGame();
    void loadTextures();
    bool movePiece(int fromX, int fromY, int toX, int toY);
    bool isPathVertical(int fromX, int fromY, int toX, int toY);
    bool isPathObstructed(int fromX, int fromY, int toX, int toY);
    void handleTile(int x, int y);
};

#endif