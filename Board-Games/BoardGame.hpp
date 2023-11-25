#ifndef BOARDGAME_HPP
#define BOARDGAME_HPP

#include <Board-Games/Tile.hpp>
#include <iostream>
#include <string>
#include <vector>

// Player1 is the player who goes first
enum class Player { Player1, Player2 };

class BoardGame {
  protected:
    int size;
    std::vector<std::vector<Tile>> board;
    Player currentPlayer;

  public:
    BoardGame(int boardSize);
    int getBoardSize() const;
    void displayBoard();
    void changePlayer();

    virtual void initializeGame() = 0;
    virtual void loadTextures() = 0;
    virtual bool movePiece(int fromX, int fromY, int toX, int toY) = 0;
};

#endif