#ifndef CHECKERS_PAWN_HPP
#define CHECKERS_PAWN_HPP

#include <Board-Games/Games/Checkers/CheckersState.hpp>
#include <Board-Games/Piece.hpp>

class CheckersPawn : public Piece {
  public:
    // Constructor
    CheckersPawn(int posX, int posY, Color pieceColor);

    bool canMove(GameState& state, int toX, int toY) const override;
    bool canCapture(GameState& state, int toX, int toY) const override;
    const std::vector<Move>* getAllAvailableMoves(GameState& state) const override;
};

#endif // CHECKERS_PA_HPP