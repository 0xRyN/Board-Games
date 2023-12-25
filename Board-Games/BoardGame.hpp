#ifndef BOARDGAME_HPP
#define BOARDGAME_HPP

class GameRules;
#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "Player.hpp"
#include "Tile.hpp"
#include "GameRules.hpp"
#include "GameState.hpp"


class BoardGame {
  protected:
    std::unique_ptr<GameState> gameState;
    std::unique_ptr<GameRules> gameRules;
    std::map<std::string, sf::Texture> textures;
  

  public:
    
    //constructors
    BoardGame();
    
    //getters
    const std::map<std::string, sf::Texture>& getTextures() const;
    GameState& getGameState() const;
    GameRules& getGameRules() const;
    
    //methods
    virtual void loadTextures();
    

   
};

#endif