#ifndef BOARDGAME_HPP
#define BOARDGAME_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "Player.hpp"
#include "Tile.hpp"
#include "GameRules.hpp"


class BoardGame {
  protected:
    int size;
    std::vector<std::vector<Tile>> board;
    std::unique_ptr<GameState> gameState;
    std::unique_ptr<GameRules> gameRules;
    std::vector<std::vector<Tile>> board;
    Player firstPlayer, secondPlayer;
    Player* currentPlayer;
    std::map<std::string, sf::Texture> textures;
    Tile* selectedTile;
  
    void updatePosition(int fromX, int fromY, int toX, int toY);
    void removeCapturedPiece(int fromX, int fromY, int toX, int toY);

  public:
    BoardGame(int boardSize);
    virtual ~BoardGame();
    void initializeGame();
    
    int getBoardSize() const;
    const std::map<std::string, sf::Texture>& getTextures() const;
    Piece* getPieceAt(int x, int y) const;
    std::vector<std::vector<Tile>>& getBoard() const;
    void selectTile(int x, int y);
    virtual void loadTextures();
    virtual void movePiece(int fromX, int fromY, int toX, int toY);
    virtual void changePlayer();
    virtual bool isEmpty(int x, int y) const;
    GameState* getGameState() const;
};

#endif