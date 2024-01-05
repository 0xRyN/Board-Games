#include <Board-Games/Piece.hpp>


class IncognitoPawn : public Piece
{
private:
    bool IsSpy;
public:
    IncognitoPawn(int posX, int posY, Color pieceColor);
    bool canMove(GameState& state, int toX, int toY) const override;
    bool isPathClear(GameState& state, int toX, int toY) const ;
    bool isASpy() const;
    void setIsASpy(bool isASpy);
    bool Ask(GameState& state, int toX, int toY) const;
    const std::vector<Move>* getAllAvailableMoves(GameState& state) const override;
    bool canCapture(GameState& state, int toX, int toY) const override;
};

