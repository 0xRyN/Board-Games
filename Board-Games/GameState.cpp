#include "GameState.hpp"

GameState::GameState() : isActionInProgress(false) {
}

void GameState::startActionSequence() {
    isActionInProgress = true;
    availableActions.clear();
}
void GameState::endActionSequence() {
    isActionInProgress = false;
    availableActions.clear();
}

bool GameState::actionInProgress() const {
    return isActionInProgress;
}

void GameState::setAvailableActions(const std::vector<std::pair<int, int>>& actions) {
    availableActions = actions;
}

const std::vector<std::pair<int, int>>& GameState::getAvailableActions() const {
    return availableActions;
}
