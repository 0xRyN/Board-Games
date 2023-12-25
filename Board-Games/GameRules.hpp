#ifndef GAME_RULES_HPP
#define GAME_RULES_HPP

class BoardGame;
#include "BoardGame.hpp"

class GameRules {
private:
    /* data */
    
public:
    virtual std::vector<std::pair<int, int>> getAvailableActions(const BoardGame& game, int x, int y) = 0;
    virtual bool isValidMove(const BoardGame& game, int fromX, int fromY, int toX, int toY) const = 0;
    // Additional methods for other game-specific rule checks
    virtual std::vector<std::pair<int, int>> getAvailableCaptureMoves(const BoardGame& game, int x, int y) = 0;
    virtual bool isValidCaptureMove(const BoardGame& game, int fromX, int fromY, int toX, int toY) = 0;

};

#endif // GAME_RULES_HPP