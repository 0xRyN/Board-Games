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



void GameState::createBoard() {
    for (int i = 0; i < boardSize; i++) {
        std::vector<Tile> row;
        for (int j = 0; j < boardSize; j++) {
            row.push_back(Tile(i, j, (i + j) % 2 == 0));
        }
        board.push_back(row);
    }
}


