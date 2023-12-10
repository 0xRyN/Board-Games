#ifndef CHECKERS_RULES_HPP
#define CHECKERS_RULES_HPP 

#include "../../GameRules.hpp"
#include "CheckersGameState.hpp"



class CheckersRules : public GameRules {
public:
    bool isValidMove(const BoardGame& game, int fromX, int fromY, int toX, int toY) const override;
    bool isCaptureMove(const BoardGame& game, int fromX, int fromY, int toX,
                       int toY) const;
    std::vector<std::pair<int, int>> getAvailableActions(const BoardGame& game,
                                                         int x, int y) override;

    //verification methods
    bool isWithinBoard(const BoardGame& game, int x, int y) const;
    bool isMoveDiagonal(int fromX, int fromY, int toX, int toY) const;
    bool isMoveForward(const BoardGame& game ,int fromX, int fromY, int toX, int toY) const;
};
#endif