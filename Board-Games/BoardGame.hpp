#ifndef BOARDGAME_HPP
#define BOARDGAME_HPP

#include <Board-Games/GameState.hpp>
#include <Board-Games/Move.hpp>
#include <Board-Games/Player.hpp>
#include <Board-Games/Tile.hpp>
#include <Board-Games/common.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>
#include <string>
#include <vector>

class BoardGame {
  protected:
    GameState* gameState;
    std::map<std::string, sf::Texture> textures;

  public:
    BoardGame(int boardSize);
    ~BoardGame();
    GameState* getGameState() const;
    const std::map<std::string, sf::Texture>& getTextures() const;
    virtual void loadTextures();
    virtual void handleTurn(Move& move);
};

#endif