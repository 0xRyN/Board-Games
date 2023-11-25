#include "Pawn.hpp"

Pawn::Pawn(int posX, int posY, Color pieceColor)
    : Piece(posX, posY, pieceColor) {
}

bool Pawn::canMove(int toX, int toY) const {
    // Movement rules for pawn :
    // 1. Can move forward one square
    // 2. Can move forward two squares if it is the first move

    // If statements are separated like this for optimization (short-circuiting)

    // Check if the pawn is moving forward
    if (toX != x) {
        return false;
    }

    // Check if the movement is more than one square and less than three squares
    if (abs(toY - y) > 2 || abs(toY - y) < 1) {
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
        if (toY >= y) {
            return false;
        }
    }

    // Check if the pawn is moving two squares
    if (abs(toY - y) == 2) {
        // Check if the pawn is in the starting position
        if (color == Color::White) {
            if (y != 1) {
                return false;
            }
        }

        if (color == Color::Black) {
            if (y != 6) {
                return false;
            }
        }
    }

    return true;
}

// TODO: Why is there fromX and fromY?
bool Pawn::canCapture(int fromX, int fromY, int toX, int toY) const {
    // Capture rules for pawn :
    // 1. Can capture diagonally forward one square
    // 2. En passant (not implemented)

    // If statements are separated like this for optimization (short-circuiting)

    // Check if the pawn is moving diagonally forward one square
    if (abs(toX - fromX) != 1 || abs(toY - fromY) != 1) {
        return false;
    }

    // White pawns can only move up the board
    if (color == Color::White) {
        if (toY <= fromY) {
            return false;
        }
    }

    // Black pawns can only move down the board
    if (color == Color::Black) {
        if (toY >= fromY) {
            return false;
        }
    }

    return true;
}
