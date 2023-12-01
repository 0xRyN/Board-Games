#ifndef CHECKERS_HPP
#define CHECKERS_HPP

#include <Board-Games/BoardGame.hpp>
#include <Board-Games/Piece.hpp>
#include <vector>
#include <utility>



class Checkers : public BoardGame {
  public:
    Checkers();
    void initializeGame();
    void loadTextures();
    bool movePiece(int fromX, int fromY, int toX, int toY);
    void updatePosition(int fromX, int fromY, int toX, int toY);
    void selectTile(int x, int y);
    bool isPathVertical(int fromX, int fromY, int toX, int toY);
    std::vector<std::pair<int, int>> computeMoves(int fromX, int fromY);
    std::vector<std::pair<int, int>> computeJumps(int fromX, int fromY, bool initialCall = true);
    bool canJump(int fromX, int fromY, int dx, int dy);
};

#endif