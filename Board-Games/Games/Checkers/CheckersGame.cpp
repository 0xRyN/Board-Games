#include "CheckersGame.hpp"
#include "CheckersGameState.hpp"
#include "CheckersRules.hpp"

CheckersGame::CheckersGame() : BoardGame(8) {
    gameState = std::make_unique<CheckersGameState>();
    gameRules = std::make_unique<CheckersRules>();
}

CheckersGame::~CheckersGame() {
}

