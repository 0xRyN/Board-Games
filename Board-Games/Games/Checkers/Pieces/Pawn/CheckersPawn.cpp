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

    // We can move, update the position
    Move move = {x, y, toX, toY, false};
    state.updatePosition(move);

    return true;
}

// TODO: Why is there fromX and fromY?
bool CheckersPawn::canCapture(GameState& state, int toX, int toY) const {
    std::cout << "Called canCapture" << std::endl;
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

    // Finally, check if the destination square is empty
    if (state.getTileAt(toX, toY).getPiece() != nullptr) {
        return false;
    }

    // We can capture, update the position
    Move move = {x, y, toX, toY, true};
    state.updatePosition(move);
    state.removeCapturedPiece(middleX, middleY);

    return true;
}

const std::vector<Move>*
CheckersPawn::getAllAvailableMoves(GameState& state) const {
    std::vector<Move>* moves = new std::vector<Move>();
    bool canCapture = false;

    for (int i = 0; i < state.getBoardSize(); ++i) {
        for (int j = 0; j < state.getBoardSize(); j++) {
            if (this->canMove(state, i, j)) {
                moves->push_back(Move(x, y, i, j, false));
            } else if (this->canCapture(state, i, j)) {
                canCapture = true;
                moves->push_back(Move(x, y, i, j, true));
            }
        }
    }

    // We can capture, remove all non-capturing moves and set the forced moves
    if (canCapture) {
        for (auto it = moves->begin(); it != moves->end();) {
            if (!it->isCaptureMove) {
                it = moves->erase(it);
            } else {
                ++it;
            }
        }
        std::cout << "Found " << moves->size() << " forced moves." << std::endl;
        for (auto move : *moves) {
            std::cout << move << std::endl;
        }
        state.setForcedMoves(*moves);
    }

    // We can't capture, remove all capturing moves and reset the forced moves
    else {
        state.setForcedMoves({});
    }

    return moves;
}
