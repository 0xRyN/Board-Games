#ifndef CHECKERS_PAWN_HPP
#define CHECKERS_PAWN_HPP

#include <Board-Games/Piece.hpp>

class CheckersPawn : public Piece {
  public:
    // Constructor
    CheckersPawn(int posX, int posY, Color pieceColor);

    bool canMove(int toX, int toY) const override;
    bool canCapture(int toX, int toY) const override;
};

#endif // CHECKERS_PA_HPP