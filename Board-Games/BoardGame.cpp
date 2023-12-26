#include "BoardGame.hpp"

BoardGame::BoardGame(int boardSize) {
    // Hardcoded, change later
    Player firstPlayer("Rayan", Color::White);
    Player secondPlayer("Ilyas", Color::Black);
    this->gameState = nullptr;
}

BoardGame::~BoardGame() {
    delete gameState;
}

GameState* BoardGame::getGameState() const {
    return gameState;
}

// Return const reference to avoid copying the map
const std::map<std::string, sf::Texture>& BoardGame::getTextures() const {
    return textures;
}

void BoardGame::loadTextures() {
    std::string textures[] = {
        "assets/Tiles/dark.png",
        "assets/Tiles/light.png",
    };

    for (std::string texture : textures) {
        sf::Texture tex;
        tex.loadFromFile(texture);
        tex.setSmooth(true);
        this->textures[texture] = tex;
    }
}

void BoardGame::handleTurn(Move& move) {
    auto fromX = move.fromX;
    auto fromY = move.fromY;

    Piece* piece = gameState->getTileAt(fromX, fromY).getPiece();

    if (piece == nullptr) {
        std::cout << "No piece at (" << fromX << ", " << fromY << ")"
                  << std::endl;
        return;
    }

    auto availableMoves =
        gameState->getAvailableMoves().at(std::make_pair(fromX, fromY));

    if (std::find(availableMoves.begin(), availableMoves.end(), move) ==
        availableMoves.end()) {
        std::cout << "Invalid move" << std::endl;
        return;
    }
    
    gameState->movePiece(move);
    gameState->changePlayer();

}