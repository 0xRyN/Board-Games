#ifndef CHECKERS_RULES_HPP
#define CHECKERS_RULES_HPP 

#include "../../GameRules.hpp"
#include "CheckersGameState.hpp"



class CheckersRules : public GameRules {
public:
    
    std::vector<std::pair<int, int>> getAvailableActions(const BoardGame& game, int x, int y) override;
    std::vector<std::pair<int, int>> getAvailableCaptureMoves(const BoardGame& game, int x, int y) override;
    
    //verification methods
    bool isValidMove(const BoardGame& game, int fromX, int fromY, int toX, int toY) const override;
    bool isValidSimpleMove(const BoardGame& game, int fromX, int fromY, int toX,int toY) const;
    bool isValidCaptureMove(const BoardGame& game, int fromX, int fromY, int toX, int toY) const;
    bool isWithinBoard(const BoardGame& game, int x, int y) const;
    bool isDiagonalStep(int step, int fromX, int fromY, int toX, int toY) const;
    bool isMoveForward(const BoardGame& game, int fromX, int fromY, int toX, int toY) const;
    bool isCapturablePiece(const BoardGame& game, int fromX, int fromY, int toX, int toY) const;
    void showReachableTiles(BoardGame& game, int x, int y) ;
};
#endif