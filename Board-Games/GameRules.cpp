
#include "GameRules.hpp"


bool GameRules::isValidCaptureMove(const BoardGame& game, int fromX, int fromY, int toX, int toY) const {
    return isValidMove(game, fromX, fromY, toX, toY);
}


bool GameRules::isValidMove(const BoardGame& game, int fromX, int fromY, int toX, int toY) const {
    return true;
}


std::vector<std::pair<int, int>> GameRules::getAvailableActions(const BoardGame& game, int x, int y){
    return std::vector<std::pair<int, int>>();
}