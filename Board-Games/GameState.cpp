#include "GameState.hpp"
#include <iostream>




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


const std::vector<std::pair<int, int>>& GameState::getAvailableActions() const {
    return availableActions;
}

const std::vector<std::vector<Tile>>& GameState::getBoard() const {
    return board;    
}

Player* GameState::getCurrentPlayer() const {
    return currentPlayer;
}

int GameState::getBoardSize() const {
    return boardSize;
}

void GameState::setBoardSize(int size) {
    boardSize = size;
}

void GameState::setBoard(const std::vector<std::vector<Tile>>& board) {
    this->board = board;
}


