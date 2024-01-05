#ifndef CHECKERSQUEEN_HPP
#define CHECKERSQUEEN_HPP

#include "Board-Games/Piece.hpp"

class CheckersQueen : public Piece {
  private:
  public:
    CheckersQueen(int posX, int posY, Color pieceColor);
    bool canCapture(GameState& state, int toX, int toY) const override;
    bool canMove(GameState& state, int toX, int toY) const override;
    const std::vector<Move>* getAllAvailableMoves(GameState& state) const override;
    void findAllCapture(GameState& state, int x, int y, int numSeq, std::vector<std::vector<Move>>* sequences, std::vector<std::vector<bool>>* visited) const;
    std::vector<Move>* findAllSimpleMoves(GameState& state, int x, int y) const;
    int countPiecesBetween(GameState& state, int toX, int toY) const;
    const Piece* getCapturedPiece(GameState& state, int x, int y, int toX,
                                  int toY) const;
};

#endif // !CHECKERSQUEEN_HPP