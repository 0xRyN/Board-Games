
#include "Checkers.hpp"
#include <Board-Games/Games/Checkers/CheckersState.hpp>
#include <Board-Games/Games/Checkers/Pieces/Pawn/CheckersPawn.hpp>
#include <Board-Games/Player.hpp>

int CHECKERS_BOARD_SIZE = 10;
Checkers::Checkers() : BoardGame(CHECKERS_BOARD_SIZE) {
    // Implementation of Checkers constructor
    Player* firstPlayer = new Player("Player 1", Color::White);
    Player* secondPlayer = new Player("Player 2", Color::Black);
    this->gameState =
        new CheckersState(CHECKERS_BOARD_SIZE, firstPlayer, secondPlayer);
}

void Checkers::loadTextures() {
    // Implementation of loadTextures function
    BoardGame::loadTextures();
    std::string textures[] = {
        "assets/Pieces/Checkers/Pawn/white.png",
        "assets/Pieces/Checkers/Pawn/black.png",

    };

    for (std::string texture : textures) {
        sf::Texture tex;
        tex.loadFromFile(texture);
        tex.setSmooth(true);
        this->textures[texture] = tex;
    }
}

void Checkers::handleTurn(Move move) {
    if (gameState->getAvailableMoves().empty()) {
        gameState->computeAvailableMoves();
    }
    BoardGame::handleTurn(move);
    //if move was a capture, check if there are any more captures for the same piece
    if(move.isCaptureMove){
        auto move = gameState->getAvailableMoves();
        move.clear();
        gameState->computeAvailableMoves();
    }
    if(gameState->getAvailableMoves().empty()){
        gameState->changePlayer();
        gameState->computeAvailableMoves();
    }
}
