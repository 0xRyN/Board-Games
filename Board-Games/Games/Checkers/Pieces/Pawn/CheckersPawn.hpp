#ifndef CHECKERS_PAWN_HPP
#define CHECKERS_PAWN_HPP

#include <Board-Games/Piece.hpp>

class CheckersPawn : public Piece {
  public:
    // Constructor
    CheckersPawn(int posX, int posY, Color pieceColor);

    // Overrides
    bool isValidMove(int toX, int toY) const override;
    bool isValidCaptureMove(int toX, int toY) const override;
};

#endif // CHECKERS_PA_HPP