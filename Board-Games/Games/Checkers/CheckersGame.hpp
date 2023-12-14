#ifndef CHECKERS_HPP
#define CHECKERS_HPP

#include "../../BoardGame.hpp"

class CheckersGame : public BoardGame {
  public:
    CheckersGame();
    ~CheckersGame();
    void removeCapturedPiece(int fromX, int fromY, int toX, int toY);
    std::vector<std::pair<int, int>> getAvailableActions(const BoardGame& game, int x, int y);
    std::vector<std::pair<int, int>> getAvailableCaptureMoves(const BoardGame& game, int x, int y);
    void setAvailableCaptureMoves(const BoardGame& game, int x, int y);
    void loadTextures() override;
};

#endif
