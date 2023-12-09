#ifndef CHECKERS_RULES_HPP
#define CHECKERS_RULES_HPP 

#include "../../GameRules.hpp"
#include "CheckersGameState.hpp"



class CheckersRules : public GameRules {
public:
    bool isValidMove(const BoardGame& game, int fromX, int fromY, int toX, int toY) const override;
    std::vector<std::pair<int, int>> getAvailableActions(const BoardGame& game, int x, int y) override;
    bool isValidCaptureMove(Piece* piece, int toX, int toY) const;
};
#endif