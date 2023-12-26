#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <Board-Games/Move.hpp>
#include <Board-Games/Player.hpp>
#include <Board-Games/Tile.hpp>
#include <Board-Games/common.hpp>

#include <iostream>
#include <map>
#include <string>
#include <vector>

class Tile;

class GameState {
  protected:
    int boardSize;
    std::vector<std::vector<Tile>> board;
    Player firstPlayer, secondPlayer;
    Player* currentPlayer;
    std::map<std::pair<int, int>, std::vector<Move>> availableMoves;

  public:
    GameState(int boardSize);
    virtual ~GameState();
    int getBoardSize() const;
    const std::vector<std::vector<Tile>>& getBoard() const;
    const Tile& getTileAt(int x, int y) const;
    const Player* getCurrentPlayer() const;
    void changePlayer();
    bool updatePosition(Move move);
    bool removeCapturedPiece(int x, int y);
    virtual void computeAvailableMoves();
    virtual void movePiece(Move move);
    virtual void initializeGame() = 0;
};

#endif