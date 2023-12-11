#include "CheckersGame.hpp"
#include "CheckersGameState.hpp"
#include "CheckersRules.hpp"

CheckersGame::CheckersGame() : BoardGame(8) {
    gameState = std::make_unique<CheckersGameState>();
    gameRules = std::make_unique<CheckersRules>();
}

CheckersGame::~CheckersGame() {
}


void CheckersGame::loadTextures() {
    // Implementation of loadTextures function
    BoardGame::loadTextures();
    std::string textures[] = {
        "assets/Pieces/Checkers/Pawn/white.png",
        "assets/Pieces/Checkers/Pawn/black.png",
    };
};

void CheckersGame::movePiece(int fromX, int fromY, int toX, int toY) {
    //get available actions
    std::vector<std::pair<int, int>> availableActions = gameRules->getAvailableActions(*this, fromX, fromY);
    //check which action is selected
    std::vector<std::pair<int, int>>::iterator selectedAction = std::find(availableActions.begin(), availableActions.end(), std::make_pair(toX, toY));
    //if action is not available, return
    if (selectedAction == availableActions.end()) {
        return;
    }
    //if action is available, move piece
    //see wich type of action is selected
    if (gameRules.

void CheckersGame::changePlayer() {
    // Implementation of changePlayer function
    BoardGame::changePlayer();
};

bool CheckersGame::isEmpty(int x, int y) const {
    // Implementation of isEmpty function
    return BoardGame::isEmpty(x, y);
};

void addAvailableCaptures(int x, int y, int dx, int dy) {

};





