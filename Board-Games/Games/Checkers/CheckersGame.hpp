#ifndef CHECKERS_HPP
#define CHECKERS_HPP

#include "../../BoardGame.hpp"

class CheckersGame : public BoardGame {
  public:
    CheckersGame();
    ~CheckersGame();
    void removeCapturedPiece(int fromX, int fromY, int toX, int toY);
    void setAvailableCaptureMoves(int x, int y);
    void setRecheableTile(int x, int y);
    void loadTextures() override;
    void initializeGame() override;
};

#endif
