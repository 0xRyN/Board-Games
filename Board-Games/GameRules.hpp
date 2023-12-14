#ifndef GAME_RULES_HPP
#define GAME_RULES_HPP

#include "BoardGame.hpp"

class GameRules {
public:
    virtual bool isValidMove(const BoardGame& game, int fromX, int fromY, int toX, int toY) const = 0;
    virtual std::vector<std::pair<int, int>> getAvailableActions(const BoardGame& game, int x, int y) = 0;
    // Additional methods for other game-specific rule checks
    virtual bool isValidCaptureMove(const BoardGame& game, int fromX, int fromY, int toX, int toY) const;

};

#endif // GAME_RULES_HPP