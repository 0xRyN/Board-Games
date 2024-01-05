#include "IncognitoPawn.hpp"

IncognitoPawn::IncognitoPawn(int posX, int posY, Color pieceColor) : Piece(posX, posY, pieceColor)
{
    texturePath = (pieceColor == Color::White) ? "assets/Pieces/Incognito/Pawn/white.png" : "assets/Pieces/Incognito/Pawn/black.png";

}

bool IncognitoPawn::canMove(GameState& state, int toX, int toY) const {
    //check if the move is diagonal or orthogonal
    if (abs(toX - x) != abs(toY - y) && toX != x && toY != y) {
        return false;
    }  

    //check if the path is clear
    if (!isPathClear(state, toX, toY)) {
        return false;
    }
    return true;
}

bool IncognitoPawn::isPathClear(GameState& state, int toX, int toY) const {
    int stepX = (toX > x) ? 1 : -1;
    int stepY = (toY > y) ? 1 : -1;

    int checkX = x + stepX;
    int checkY = y + stepY;

    while (checkX != toX || checkY != toY) {
        if (state.getPiece(checkX, checkY) != nullptr) {
            return false;
        }
        checkX += stepX;
        checkY += stepY;
    }

    return true;
}

bool IncognitoPawn::isASpy() const {
    return this->IsSpy;
}

void IncognitoPawn::setIsASpy(bool isASpy) {
    this->IsSpy = isASpy;
}

bool IncognitoPawn::Ask(GameState& state, int toX, int toY) const {
    //check if the piece to ask is adjacent orthogonally
    if (abs(toX - x) > 1 || abs(toY - y) > 1) {
        std::cout << "You can only ask about adjacent orthogonally pieces" << std::endl;
        return false;
    }

    const IncognitoPawn* pieceToAsk = const_cast<IncognitoPawn*>(dynamic_cast<const IncognitoPawn*>(state.getPiece(toX, toY)));

    if (pieceToAsk->isASpy()) {
        std::cout << "The piece is a spy" << std::endl;
        return true;
    }
    
    std::cout << "The piece is not a spy" << std::endl;
    return false;

    
}

const std::vector<Move>*
IncognitoPawn::getAllAvailableMoves(GameState& state) const {
    //just iterate through all the board and check if the piece can move there 
    std::vector<Move>* moves = new std::vector<Move>();
    for (int i = 0; i < state.getBoardSize(); i++) {
        for (int j = 0; j < state.getBoardSize(); j++) {
            if (canMove(state, i, j)) {
                moves->push_back(Move(x, y, i, j , false));
            }
        }
    }
    return moves;
}

bool IncognitoPawn::canCapture(GameState& state, int toX, int toY) const {
    return false;
}
