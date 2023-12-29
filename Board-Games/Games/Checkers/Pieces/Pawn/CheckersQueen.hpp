#ifndef CHECKERSQUEEN_HPP
#define CHECKERSQUEEN_HPP

#include "Piece.hpp"

class CheckersQueen : public Piece{
private:
    /* data */
public:
    CheckersQueen(int posX, int posY, Color pieceColor);
    
    bool canCapture(GameState& state, int toX, int toY) const override;
    bool canMove(GameState& state, int toX, int toY) const override;
    bool checkPath(GameState& state, int toX, int toY) const;
    const std::vector<Move>*
    getAllAvailableMoves(GameState& state) const override;
};
 
#endif // !CHECKERSQUEEN_HPP