#ifndef CHESS_HPP
#define CHESS_HPP

#include <Board-Games/BoardGame.hpp>
#include <Board-Games/Piece.hpp>

class Chess : public BoardGame {
  public:
    Chess();
    void initializeGame();
    bool movePiece(int fromX, int fromY, int toX, int toY);
};

#endif