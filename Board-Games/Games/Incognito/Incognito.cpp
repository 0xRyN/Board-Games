#include "Incognito.hpp"
#include "IncognitoState.hpp"
#include <Board-Games/Games/Incognito/Pieces/IncognitoPawn.hpp>


Incognito::Incognito() : BoardGame(5) {
    // Implementation of Checkers constructor
    Player* firstPlayer = new Player("Player 1", Color::White);
    Player* secondPlayer = new Player("Player 2", Color::Black);
    this->gameState =
        new IncognitoState(5, firstPlayer, secondPlayer);
}

void Incognito::loadTextures() {
    // Implementation of loadTextures function
    BoardGame::loadTextures();
    std::string textures[] = {
    "assets/Pieces/Incognito/Pawn/white.png",
    "assets/Pieces/Incognito/Pawn/black.png",

    };

    for (std::string texture : textures) {
        sf::Texture tex;
        tex.loadFromFile(texture);
        tex.setSmooth(true);
        this->textures[texture] = tex;
    }
}

bool Incognito::handleTurn(Move& move) {
    int toX = move.toX;
    int toY = move.toY;

    if (gameState->getTileAt(toX, toY).getPiece() != nullptr) {
        IncognitoPawn *piece = dynamic_cast<IncognitoPawn *>(gameState->getTileAt(toX, toY).getPiece());
        bool isASpy = piece->Ask(*gameState, toX, toY);
        if (isASpy) {
            std::cout << "This is a spy" << std::endl;
        }
    }else{
        BoardGame::handleTurn(move);
    }
    
    gameState->changePlayer();
    gameState->computeAvailableMoves();

    return true;
}