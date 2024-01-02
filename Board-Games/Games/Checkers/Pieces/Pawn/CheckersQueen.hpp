#ifndef CHECKERSQUEEN_HPP
#define CHECKERSQUEEN_HPP

#include "Board-Games/Piece.hpp"

class CheckersQueen : public Piece {
  private:
  public:
    CheckersQueen(int posX, int posY, Color pieceColor);
    bool canCapture(GameState& state, int toX, int toY) const override;
    bool canMove(GameState& state, int toX, int toY) const override;

    int countPiecesBetween(GameState& state, int toX, int toY) const;
};

#endif // !CHECKERSQUEEN_HPP