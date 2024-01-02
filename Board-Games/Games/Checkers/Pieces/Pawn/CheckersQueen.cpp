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
    //check if the piece is moving diagonally
    if (abs(toX - x) != abs(toY - y)) {
        return false;
    }
    //piece count
    int pieceCount = 0;


    
    // check the number of pieces between the current position and the target

    
}


bool CheckersQueen::canMove(GameState& state, int toX, int toY) const {
    return false;
}


//make a function that counts the number of pieces between the current position and the target position
int CheckersQueen::countPiecesBetween(GameState& state, int toX, int toY) const {
    int pieceCount = 0;
    int xDir = (toX - x) / abs(toX - x);
    int yDir = (toY - y) / abs(toY - y);
    int xTemp = x;
    int yTemp = y;
    while (xTemp != toX && yTemp != toY) {
        xTemp += xDir;
        yTemp += yDir;
        if (state.getPiece(xTemp, yTemp) != nullptr) {
            pieceCount++;
        }
    }
    return pieceCount;
}