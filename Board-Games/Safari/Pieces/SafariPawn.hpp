#ifndef SAFARI_PAWN_HPP
#define SAFARI_PAWN_HPP

#include "Piece.hpp"

class SafariPawn : public Piece {
    // Add class members and methods here
  private:
    /* data */

  public:
    SafariPawn(int posX, int posY, Color pieceColor);
    bool canMove(GameState& state, int toX, int toY) const override;
    bool isPathClear(GameState& state, int toX, int toY) const;
    bool Ask(GameState& state, int toX, int toY) const;
    const std::vector<Move>* getAllAvailableMoves(GameState& state) const override;
    bool canCapture(GameState& state, int toX, int toY) const override;
};

#endif // SAFARI_PAWN_HPP
