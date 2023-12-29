#include "CheckersQueen.hpp"

CheckersQueen::CheckersQueen(int posX, int posY, Color pieceColor)
    : Piece(posX, posY, pieceColor) {
    texturePath = (pieceColor == Color::White)
                      ? "assets/Pieces/Checkers/Queen/light.png"
                      : "assets/Pieces/Checkers/Queen/dark.png";
}

bool CheckersQueen::canMove(GameState& state, int toX, int toY) const {
    // Check if the queen is moving diagonally
    if (abs(toX - x) != abs(toY - y)) {
        return false;
    }

    // Check if there is a piece in the destination square
    if (state.getTileAt(toX, toY).getPiece() != nullptr) {
        return false;
    }

    return true;
}

bool CheckersQueen::canCapture(GameState& state, int toX, int toY) const {
    // Check if the queen is moving diagonally
    if (abs(toX - x) != abs(toY - y)) {
        return false;
    }

    // Check if there is a piece in the destination square
    if (state.getTileAt(toX, toY).getPiece() != nullptr) {
        return false;
    }
    // check if there is a piece adjacent to the destination square & if it is
    // the opposite color
    int xDir = (toX - x) / abs(toX - x);
    int yDir = (toY - y) / abs(toY - y);
    if (state.getTileAt(toX - xDir, toY - yDir).getPiece() == nullptr &&
        state.getTileAt(toX - xDir, toY - yDir).getPiece()->getColor() !=
            color) {
        return false;
    }
    return true;
}

const std::vector<Move>*
CheckersQueen::getAllAvailableMoves(GameState& state) const {
    std::vector<Move>* moves = new std::vector<Move>();
    // run isValidMove for all possible tiles diagonally from the queen

    bool capture = false;
    for (int i = 1; i < 8; i++) {
        if (isValidMove(state, x + i, y + i)) {
            capture = canCapture(state, x + i, y + i);
            moves->push_back(Move(x, y, x + i, y + i, capture));
        }
        if (isValidMove(state, x - i, y + i)) {
            capture = canCapture(state, x - i, y + i);
            moves->push_back(Move(x, y, x - i, y + i, capture));
        }
        if (isValidMove(state, x + i, y - i)) {
            capture = canCapture(state, x + i, y - i);
            moves->push_back(Move(x, y, x + i, y - i, capture));
        }
        if (isValidMove(state, x - i, y - i)) {
            capture = canCapture(state, x - i, y - i);
            moves->push_back(Move(x, y, x - i, y - i, capture));
        }
    }

    return moves;
}
