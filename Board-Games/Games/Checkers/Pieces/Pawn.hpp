#ifndef PAWN_HPP
#define PAWN_HPP

#include <Board-Games/Piece.hpp>

class Pawn : public Piece {
  public:
    // Constructor
    Pawn(int posX, int posY, Color pieceColor);

    // Overrides
    bool canMove(int toX, int toY) const override;
    bool canCapture(int toX, int toY) const override;
};

#endif // PAWN_HPP