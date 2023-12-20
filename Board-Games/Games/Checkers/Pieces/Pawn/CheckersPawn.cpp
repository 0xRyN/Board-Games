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

bool CheckersPawn::checkDirAndStep(int toX, int toY, int step) const {
    if (abs(toX - x) != step || abs(toY - y) != step) {
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

    return true;
}

bool CheckersPawn::canMove(GameState& state, int toX, int toY) const {
    // Movement rules for pawn checkers :
    // 1. Can move diagonally forward one square
    // If statements are separated like this for optimization (short-circuiting)

    // Check if the pawn is moving diagonally forward one square
    if(!checkDirAndStep(toX, toY, 1)) {
        return false;
    }
    

    // Check if there is a piece in the destination square
    if (state.getTileAt(toX, toY).getPiece() != nullptr) {
        return false;
    }

    // We can move, update the position
/*     Move move = {x, y, toX, toY, false};
    state.updatePosition(move, false); */

    return true;
}

// TODO: Why is there fromX and fromY?
bool CheckersPawn::canCapture(GameState& state, int toX, int toY) const {
    if (!checkDirAndStep(toX, toY, 2)) {
        return false;
    }

    // We need to check if there is a piece in the middle of the move
    // If there is no piece, then the move is invalid
    int middleX = (toX + x) / 2;
    int middleY = (toY + y) / 2;

    if (state.getTileAt(middleX, middleY).getPiece() == nullptr) {
        return false;
    }
    // We need to check if the piece in the middle is of the opposite color
    // If it is not, then the move is invalid
    if (state.getTileAt(middleX, middleY).getPiece()->getColor() == color) {
        return false;
    }
    // Finally, check if the destination square is empty
    if (state.getTileAt(toX, toY).getPiece() != nullptr) {
        return false;
    }

    // We can capture, update the position
/*     Move move = {x, y, toX, toY, true};
    state.updatePosition(move, true); */
    return true;
}

void CheckersPawn::getAllAvailableMoves(GameState& state) const {
    std::vector<Move>* moves = new std::vector<Move>();
    bool canCapture = false;

    for (int i = 0; i < state.getBoardSize(); ++i) {
        for (int j = 0; j < state.getBoardSize(); j++) {
            if (this->canMove(state, i, j)) {
                moves->push_back(Move(x, y, i, j, false));
            } else if (this->canCapture(state, i, j)) {
                canCapture = true;
                std::cout << "Can capture at (" << i << ", " << j << ")"
                          << std::endl;
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
        state.setForcedMoves(*moves);
    }
}

