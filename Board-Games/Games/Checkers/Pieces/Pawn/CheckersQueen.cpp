#include "CheckersQueen.hpp"

CheckersQueen::CheckersQueen(int posX, int posY, Color pieceColor) 
    : Piece(posX, posY, pieceColor) {
    texturePath = (pieceColor == Color::White)
                      ? "assets/Pieces/Checkers/Queen/light.png"
                      : "assets/Pieces/Checkers/Queen/dark.png";
}

bool CheckersQueen::canMove(GameState& state, int toX, int toY) const {
    //Check if the queen is moving diagonally
    if (abs(toX - x) != abs(toY - y)) {
        return false;
    }

    // Check if there is a piece in the destination square
    if (state.getTileAt(toX, toY).getPiece() != nullptr) {
        return false;
    }

    return true;
}

const std::vector<Move>*
CheckersQueen::getAllAvailableMoves(GameState& state) const {
    std::vector<Move>* moves = new std::vector<Move>();
    int xDir = (state.getCurrentPlayer()->getColor() == Color::White) ? 1 : -1;
    int yDir = (state.getCurrentPlayer()->getColor() == Color::White) ? 1 : -1;

    // Check if the queen can move diagonally
    for (int i = 1; i < state.getBoardSize(); i++) {
        if (x + i * xDir >= state.getBoardSize() || x + i * xDir < 0 ||
            y + i * yDir >= state.getBoardSize() || y + i * yDir < 0) {
            break;
        }
        if (canMove(state, x + i * xDir, y + i * yDir)) {
            moves->push_back(Move(x, y, x + i * xDir, y + i * yDir , false));
        } else {
            break;
        }
    }

    // Check if the queen can capture diagonally
    for (int i = 1; i < state.getBoardSize(); i++) {
        if (x + i * xDir >= state.getBoardSize() || x + i * xDir < 0 ||
            y + i * yDir >= state.getBoardSize() || y + i * yDir < 0) {
            break;
        }
        if (canCapture(state, x + i * xDir, y + i * yDir)) {
            moves->push_back(Move(x, y, x + i * xDir, y + i * yDir, true));
        } else {
            break;
        }
    }

    return moves;
    
}

bool CheckersQueen::canCapture(GameState& state, int toX, int toY) const {
        //check if there is a piece adjacent to the destination square
    int xDir = (toX - x) / abs(toX - x);
    int yDir = (toY - y) / abs(toY - y);
    if (state.getTileAt(toX - xDir, toY - yDir).getPiece() == nullptr) {
        return false;
    }
    return true;
}





