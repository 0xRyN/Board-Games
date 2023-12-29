#ifndef CHECKERSQUEEN_HPP
#define CHECKERSQUEEN_HPP

#include "Board-Games/Piece.cpp"

class CheckersQueen : public Piece{
private:

public:
    CheckersQueen(int posX, int posY, Color pieceColor);
    
    bool canCapture(GameState& state, int toX, int toY) const override;
    bool canMove(GameState& state, int toX, int toY) const override;
    const std::vector<Move>*
    getAllAvailableMoves(GameState& state) const override;
};
 
#endif // !CHECKERSQUEEN_HPP