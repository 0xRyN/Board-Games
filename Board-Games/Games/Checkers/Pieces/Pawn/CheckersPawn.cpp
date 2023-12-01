#include "CheckersPawn.hpp"
#include <iostream>
#include <vector>

CheckersPawn::CheckersPawn(int posX, int posY, Color pieceColor)
    : Piece(posX, posY, pieceColor) {
    texturePath = (pieceColor == Color::White)
                      ? "assets/Pieces/Checkers/Pawn/white.png"
                      : "assets/Pieces/Checkers/Pawn/black.png";
}

bool CheckersPawn::isValidMove(int toX, int toY) const {
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

    return true;
}

// TODO: Why is there fromX and fromY?
bool CheckersPawn::isValidJump(int toX, int toY) const {
   // Check if the pawn is moving diagonally forward two square
   if(this->color == Color::White){
       if(toY - y == 2 && abs(toX - x) == 2){
           return true;
       }
   }
   else if(this->color == Color::Black){
       if(y - toY == 2 && abs(toX - x) == 2){
           return true;
       }
   }
    return false;
}




