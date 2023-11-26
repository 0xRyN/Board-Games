#include "CheckersPawn.hpp"

CheckersPawn::CheckersPawn(int posX, int posY, Color pieceColor)
    : Piece(posX, posY, pieceColor) {
}

bool CheckersPawn::canMove(int toX, int toY) const {
    // Movement rules for pawn checkers :
    // 1. Can move diagonally forward one square
    // If statements are separated like this for optimization (short-circuiting)

    // Check if the pawn is moving diagonally forward one square
    if (abs(toX - x) != 1 || abs(toY - y) != 1) {
        return false;
    }

    // White pawns can only move up the board
    if (color == Color::White) {
        if (toY <= y) {
            return false;
        }
    }

    // Black pawns can only move down the board
    if (color == Color::Black) {
        if (toY >= x) {
            return false;
        }
    }

    return true;
}

// TODO: Why is there fromX and fromY?
bool CheckersPawn::canCapture(int toX, int toY) const {
    // Capture rules for pawn checkers :
    // 1. Can move diagonally forward two squares
    // 2. Can move diagonally forward one square
    // If statements are separated like this for optimization (short-circuiting)

    // Check if the pawn is moving diagonally forward two square
    if (abs(toX - x) != 2 || abs(toY - y) != 2) {
        return false;
    }
}
