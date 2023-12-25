#include "BoardGame.hpp"


const std::map<std::string, sf::Texture>& BoardGame::getTextures() const {
    return textures;
}

GameState& BoardGame::getGameState() const {
    return *gameState;
}

GameRules& BoardGame::getGameRules() const {
    return *gameRules;
}




