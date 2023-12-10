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
  
    bool isPathClear(int fromX, int fromY, int toX, int toY) const;
    void updatePosition(int fromX, int fromY, int toX, int toY);
    void removeCapturedPiece(int fromX, int fromY, int toX, int toY);

  public:
    BoardGame(int boardSize);
    int getBoardSize() const;
    const std::vector<std::vector<Tile>>& getBoard() const;
    const std::map<std::string, sf::Texture>& getTextures() const;
    Piece* getPieceAt(int x, int y) const;
    void displayBoard();
    void changePlayer();
    void selectTile(int x, int y);
    virtual void loadTextures();
    virtual void initializeGame() = 0;
    virtual void movePiece(int fromX, int fromY, int toX, int toY);
    GameState* getGameState() const;
};

#endif