
#include "Checkers.hpp"
#include <Board-Games/Games/Checkers/CheckersState.hpp>
#include <Board-Games/Games/Checkers/Pieces/Pawn/CheckersPawn.hpp>
#include <Board-Games/Player.hpp>

int CHECKERS_BOARD_SIZE = 8;
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
        "assets/Pieces/Checkers/Queen/light.png",
        "assets/Pieces/Checkers/Queen/dark.png",
    };

    for (std::string texture : textures) {
        sf::Texture tex;
        tex.loadFromFile(texture);
        tex.setSmooth(true);
        this->textures[texture] = tex;
    }
}

bool Checkers::handleTurn(Move& move) {
    bool isMoveValid = BoardGame::handleTurn(move);
    if (!isMoveValid) {
        return false;
    }

    Piece* piece = gameState->getTileAt(move.toX, move.toY).getPiece();

    if (piece == nullptr) {
        std::cout << "No piece at (" << move.toX << ", " << move.toY << ")"
                  << std::endl;
        return false;
    }

    auto availableMoves = piece->getAllAvailableMoves(*gameState);

    bool captureAvailable = false;
    for (auto& move : *availableMoves) {
        if (move.isCaptureMove) {
            captureAvailable = true;
            break;
        }
    }

    delete availableMoves;

    if (!captureAvailable || !move.isCaptureMove) {
        gameState->changePlayer();
    }

    if(typeid(*piece).name() == typeid(CheckersPawn).name()) {
        CheckersPawn* pawn = dynamic_cast<CheckersPawn*>(piece);
        if(pawn->canBePromoted(*gameState)) {
            dynamic_cast<CheckersState*>(gameState)->promotePawn(move.toX, move.toY);
        }
    }
    gameState->computeAvailableMoves();

    return true;
}
