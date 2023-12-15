#ifndef CHECKERS_HPP
#define CHECKERS_HPP

#include "../../BoardGame.hpp"

class CheckersGame : public BoardGame {
  public:
    CheckersGame();
    ~CheckersGame();
    void removeCapturedPiece(int fromX, int fromY, int toX, int toY);
    std::vector<std::pair<int, int>> getAvailableActions(int x, int y);
    std::vector<std::pair<int, int>> getAvailableCaptureMoves(int x, int y);
    void setAvailableCaptureMoves(int x, int y);
    void setRecheableTile(int x, int y);
    void loadTextures() override;
    void setRecheableTile(BoardGame& game, int x, int y);
};

#endif
