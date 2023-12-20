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
    void getAllAvailableMoves(GameState& state) const override;
    bool checkDirAndStep (int toX, int toY, int step) const;
};

#endif // CHECKERS_PA_HPP