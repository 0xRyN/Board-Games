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

bool BoardGame::handleTurn(Move& move) {
    auto fromX = move.fromX;
    auto fromY = move.fromY;

    Piece* piece = gameState->getTileAt(fromX, fromY).getPiece();

    if (piece == nullptr) {
        std::cout << "No piece at (" << fromX << ", " << fromY << ")"
                  << std::endl;
        return false;
    }

    auto allAvailableMoves = gameState->getAvailableMoves();

    auto it = allAvailableMoves.find(std::make_pair(fromX, fromY));
    if (it == allAvailableMoves.end()) {
        std::cout << "No available moves for this piece" << std::endl;
        // TODO: REMOVE THIS
        // Print all available moves
        for (auto& pair : allAvailableMoves) {
            for (auto& move : pair.second) {
                std::cout << move << std::endl;
            }
        }
        return false;
    }

    std::vector<Move> pieceAvailableMoves = it->second;

    auto validMoveIt =
        std::find(pieceAvailableMoves.begin(), pieceAvailableMoves.end(), move);

    if (validMoveIt == pieceAvailableMoves.end()) {
        std::cout << "Invalid move" << std::endl;
        return false;
    }

    // Correct the move if it's a capture move (because GameView doesn't know
    // and always sends a non-capture move)
    if (validMoveIt->isCaptureMove) {
        move.isCaptureMove = true;
    }

    gameState->movePiece(move);

    return true;
}