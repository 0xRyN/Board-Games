#ifndef BOARDGAME_HPP
#define BOARDGAME_HPP

#include <Board-Games/Tile.hpp>
#include <Board-Games/common.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>
#include <string>
#include <vector>

class BoardGame {
  protected:
    int size;
    std::vector<std::vector<Tile>> board;
    Player currentPlayer;
    std::map<std::string, sf::Texture> textures;
    Tile* selectedTile;

  public:
    BoardGame(int boardSize);
    int getBoardSize() const;
    const std::vector<std::vector<Tile>>& getBoard() const;
    const std::map<std::string, sf::Texture>& getTextures() const;
    Piece* getPieceAt(int x, int y) const;
    void displayBoard();
    void changePlayer();
    virtual void handleTile(int x, int y);
    int playerToInt() const;
    virtual void loadTextures();
    virtual void initializeGame() = 0;
    virtual bool movePiece(int fromX, int fromY, int toX, int toY) = 0;
};

#endif