#include "CheckersQueen.hpp"

#include <iostream>

CheckersQueen::CheckersQueen(int posX, int posY, Color pieceColor)
    : Piece(posX, posY, pieceColor) {
    texturePath = (pieceColor == Color::White)
                      ? "assets/Pieces/Checkers/Queen/light.png"
                      : "assets/Pieces/Checkers/Queen/dark.png";
}

bool isWithinBounds(int x, int y, int boardSize) {
    if (x < 0 || x >= boardSize || y < 0 || y >= boardSize) {
        return false;
    }
    return true;
}

bool CheckersQueen::canCapture(GameState& state, int toX, int toY) const {
    // check if the piece is moving diagonally
    if (abs(toX - x) != abs(toY - y)) {
        return false;
    }
    // check if the destination is free
    if (state.getPiece(toX, toY) != nullptr) {
        return false;
    }

    // piece count
    if (countPiecesBetween(state, toX, toY) != 1) {
        return false;
    }

    return true;
}

bool CheckersQueen::canMove(GameState& state, int toX, int toY) const {
    if (abs(toX - x) != abs(toY - y)) {
        return false;
    }
    if (state.getPiece(toX, toY) != nullptr) {
        return false;
    }
    if (countPiecesBetween(state, toX, toY) != 0) {
        return false;
    }
    return true;
}

const std::vector<Move>*
CheckersQueen::getAllAvailableMoves(GameState& state) const {
    std::vector<Move>* moves = new std::vector<Move>();
    std::vector<std::vector<Move>>* sequences =
        new std::vector<std::vector<Move>>();
    // visited array initialized to false at all positions
    std::vector<std::vector<bool>>* visited =
        new std::vector<std::vector<bool>>();
    for (int i = 0; i < state.getBoardSize(); ++i) {
        std::vector<bool> row;
        for (int j = 0; j < state.getBoardSize(); ++j) {
            row.push_back(false);
        }
        visited->push_back(row);
    }

    findAllCapture(state, x, y, 0, sequences, visited);

    // take the longest sequence
    int maxSeq = 0;
    if (sequences->size() > 0) {
        for (size_t i = 0; i < sequences->size(); ++i) {
            if (sequences->at(i).size() > sequences->at(maxSeq).size()) {
                maxSeq = i;
            }
        }
        moves = &sequences->at(maxSeq);

    } else

        moves = findAllSimpleMoves(state, x, y);

    return moves;
}
void CheckersQueen::findAllCapture(
    GameState& state, int x, int y, int numSeq,
    std::vector<std::vector<Move>>* sequences,
    std::vector<std::vector<bool>>* visited) const {
    // Check all diagonal directions
    int directions[4][2] = {{-1, -1}, {-1, 1}, {1, -1}, {1, 1}};
    for (int i = 0; i < 4; ++i) {
        int dx = directions[i][0];
        int dy = directions[i][1];
        int xTemp = x;
        int yTemp = y;
        while (isWithinBounds(xTemp + dx, yTemp + dy, state.getBoardSize())) {
            if (canCapture(state, xTemp + dx, yTemp + dy)) {
                // mark the captured position as visited
                Piece* capturedPiece =
                    (Piece*)getCapturedPiece(state, x, y, xTemp + dx, yTemp + dy);
                visited->at(capturedPiece->getX()).at(capturedPiece->getY()) = true;
                // add the move to the sequence
                std::vector<Move> sequence;
                sequence.push_back(Move(x, y, xTemp + dx, yTemp + dy, true));
                sequences[numSeq].push_back(sequence);
                // find all the possible sequences from the new position
                numSeq++;
                findAllCapture(state, xTemp + dx, yTemp + dy, numSeq, sequences,
                               visited);
            }
        }
        dx += directions[i][0];
        dy += directions[i][1];
    }
}


std::vector<Move>* CheckersQueen::findAllSimpleMoves(GameState& state, int x,
                                                     int y) const {
    std::vector<Move>* moves = new std::vector<Move>();
    // Check all diagonal directions
    int directions[4][2] = {{-1, -1}, {-1, 1}, {1, -1}, {1, 1}};
    for (int i = 0; i < 4; ++i) {
        int dx = directions[i][0];
        int dy = directions[i][1];
        int xTemp = x;
        int yTemp = y;
        while (isWithinBounds(xTemp + dx, yTemp + dy, state.getBoardSize()) &&
               canMove(state, xTemp + dx, yTemp + dy)) {
            moves->push_back(Move(x, y, xTemp + dx, yTemp + dy, false));
            xTemp += dx;
            yTemp += dy;
        }
    }

    return moves;
}

// make a function that counts the number of pieces between the
// current position and the target position
int CheckersQueen::countPiecesBetween(GameState& state, int toX,
                                      int toY) const {
    int pieceCount = 0;
    int xDir = (toX - x) / abs(toX - x);
    int yDir = (toY - y) / abs(toY - y);
    int xTemp = x;
    int yTemp = y;
    while (xTemp != toX && yTemp != toY) {
        xTemp += xDir;
        yTemp += yDir;
        if (state.getPiece(xTemp, yTemp) != nullptr &&
            state.getPiece(xTemp, yTemp)->getColor() != color) {
            pieceCount++;
        }
    }
    return pieceCount;
}

const Piece* CheckersQueen::getCapturedPiece(GameState& state, int x, int y,
                                             int toX, int toY) const {
    const Piece* capturedPiece = nullptr;
    int xDir = (toX - x == 0) ? 0 : (toX - x) / abs(toX - x);
    int yDir = (toY - y == 0) ? 0 : (toY - y) / abs(toY - y);
    int xTemp = x;
    int yTemp = y;
    while (xTemp != toX && yTemp != toY) {
        xTemp += xDir;
        yTemp += yDir;
        if (state.getPiece(xTemp, yTemp) != nullptr &&
            state.getPiece(xTemp, yTemp)->getColor() != color) {
            capturedPiece = state.getPiece(xTemp, yTemp);
            break;
        }
    }

    return capturedPiece;
}
