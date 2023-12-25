#include "BoardGame.hpp"

BoardGame::BoardGame() {
    loadTextures();
}

const std::map<std::string, sf::Texture>& BoardGame::getTextures() const {
    return textures;
}

GameState& BoardGame::getGameState() const {
    return *gameState;
}

GameRules& BoardGame::getGameRules() const {
    return *gameRules;
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


