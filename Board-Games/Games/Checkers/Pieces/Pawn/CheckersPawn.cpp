#include "CheckersPawn.hpp"
#include <Board-Games/common.hpp>
#include <iostream>
#include <vector>

CheckersPawn::CheckersPawn(int posX, int posY, Color pieceColor)
    : Piece(posX, posY, pieceColor) {
    texturePath = (pieceColor == Color::White)
                      ? "assets/Pieces/Checkers/Pawn/white.png"
                      : "assets/Pieces/Checkers/Pawn/black.png";
}

bool CheckersPawn::canMove(GameState& state, int toX, int toY) const {
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
            std::cout << "White pawns can only move up the board" << std::endl;
            return false;
        }
    }

    // Black pawns can only move down the board
    if (color == Color::Black) {
        if (toY >= y) {
            return false;
        }
    }

    // Check if there is a piece in the destination square
    if (state.getTileAt(toX, toY).getPiece() != nullptr) {
        return false;
    }
    return true;
}

// TODO: Why is there fromX and fromY?
bool CheckersPawn::canCapture(GameState& state, int toX, int toY) const {
    if (abs(toX - x) != 2 || abs(toY - y) != 2) {
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

    // We need to check if there is a piece in the middle of the move
    // If there is no piece, then the move is invalid
    int middleX = (toX + x) / 2;
    int middleY = (toY + y) / 2;

    if (state.getTileAt(middleX, middleY).getPiece() == nullptr) {
        return false;
    }

    // Check if the piece in the middle is of the opposite color
    if (state.getTileAt(middleX, middleY).getPiece()->getColor() == color) {
        return false;
    }

    // Finally, check if the destination square is empty
    if (state.getTileAt(toX, toY).getPiece() != nullptr) {
        return false;
    }
    return true;
}

const std::vector<Move>*
CheckersPawn::getAllAvailableMoves(GameState& state) const {
    std::vector<Move>* moves = new std::vector<Move>();

    const int WHITE_DIRECTION = 1;
    const int BLACK_DIRECTION = -1;

    // Utiliser les constantes dans le code
    int direction = (color == Color::White) ? WHITE_DIRECTION : BLACK_DIRECTION;

    // Iterate through all possible moves in the valid direction
    for (int dx = -1; dx <= 1; dx += 2) {
        // For simple moves
        int toX = x + dx;
        int toY = y + direction;

        // For capture moves
        int captureX = x + 2 * dx;
        int captureY = y + 2 * direction;

        // Check if the move is valid
        if (isValidMove(state, toX, toY)) {
            moves->push_back(Move(x, y, toX, toY, false));
        }

        // Check if the capture move is valid
        if (isValidMove(state, captureX, captureY)) {
            moves->push_back(Move(x, y, captureX, captureY, true));
        }
    }
    return moves;
}

bool CheckersPawn::canBePromoted(GameState& state) const {
    // Check if the pawn is at the end of the board
    if (color == Color::White) {
        if (y == state.getBoardSize() - 1) {
            return true;
        }
    }

    if (color == Color::Black) {
        if (y == 0) {
            return true;
        }
    }

    return false;
}
