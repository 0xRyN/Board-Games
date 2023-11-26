#ifndef BOARDGAME_HPP
#define BOARDGAME_HPP

#include <Board-Games/Tile.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>
#include <string>
#include <vector>

// Player1 is the player who goes first
enum class Player { Player1, Player2 };

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
    const std::map<std::string, sf::Texture>& getTextures() const;
    Piece* getPieceAt(int x, int y) const;
    void displayBoard();
    void changePlayer();

    virtual void initializeGame() = 0;
    virtual void loadTextures() = 0;
    virtual bool movePiece(int fromX, int fromY, int toX, int toY) = 0;
};

#endif