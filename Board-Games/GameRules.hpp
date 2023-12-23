#ifndef GAME_RULES_HPP
#define GAME_RULES_HPP

class BoardGame;
#include "BoardGame.hpp"

class GameRules {
public:
    virtual std::vector<std::pair<int, int>> getAvailableCaptureMoves(const BoardGame& game, int x, int y) ;
    virtual bool isValidMove(const BoardGame& game, int fromX, int fromY, int toX, int toY) const = 0;
    virtual std::vector<std::pair<int, int>> getAvailableActions(const BoardGame& game, int x, int y);
    // Additional methods for other game-specific rule checks
    virtual bool isValidCaptureMove(const BoardGame& game, int fromX, int fromY, int toX, int toY) ;

};

#endif // GAME_RULES_HPP