#include "CheckersRules.hpp"

bool CheckersRules::isValidMove(const BoardGame& game, int fromX, int fromY,
                                int toX, int toY) const {
    if(!isWithinBoard(game, toX, toY)) {
        return false;
    }
    if(isValidSimpleMove(game, fromX, fromY, toX, toY)){
        return true;
    }
    if(isValidCaptureMove(game, fromX, fromY, toX, toY)){
        return true;
    }
    return false;
}

bool CheckersRules::isValidCaptureMove(const BoardGame& game, int fromX, int fromY,
                                  int toX, int toY) const {

    // Check if the move is diagonal and of length 2
    if (!isDiagonalStep(2,fromX, fromY, toX, toY)) {
        return false;
    }

    // check if the piece is of the opposite color
    if (!isCapturablePiece(game, fromX, fromY, toX, toY)) {
        return false;
    }

    // Check if the destination square is empty
    if (!game.isEmpty(toX, toY)) {
        return false;
    }

    return true;
}



bool CheckersRules::isValidSimpleMove(const BoardGame& game, int fromX, int fromY,
                                 int toX, int toY) const {
    // check if the move is diagonal
    if (!isDiagonalStep(1, fromX, fromY, toX, toY)) {
        return false;
    }
    // check if the move is forward
    if (!isMoveForward(game, fromX, fromY, toX, toY)) {
        return false;
    }
    // check if the tile is empty
    if (game.getPieceAt(toX, toY) != nullptr) {
        return false;
    }
    return true;
}

bool CheckersRules::isWithinBoard(const BoardGame& game, int x, int y) const {
    return x >= 0 && x < game.getBoardSize() && y >= 0 &&
           y < game.getBoardSize();
}

bool CheckersRules::isDiagonalStep(int step,int fromX, int fromY, int toX,
                                   int toY) const {
    // check if the move is diagonal and of length 1
    return abs(fromX - toX) == step && abs(fromY - toY) == step;
}


bool CheckersRules::isMoveForward(const BoardGame& game, int fromX, int fromY,
                                  int toX, int toY) const {
    // if the piece is white, it can only move down
    if (game.getPieceAt(fromX, fromY)->getColor() == Color::White) {
        return fromY < toY;
    }
    // if the piece is black, it can only move up
    return fromY > toY;
}

bool CheckersRules::isCapturablePiece(const BoardGame& game, int fromX, int fromY,
                                  int toX, int toY) const { 
    // Get the position of the jumped piece
    int midX = (fromX + toX) / 2;
    int midY = (fromY + toY) / 2;
    Piece* jumpedPiece = game.getPieceAt(midX, midY);

    // Check if there is a piece to jump over and it's of the opposite color
    if (jumpedPiece == nullptr) {
        return false;
    }
    Color color = game.getPieceAt(fromX, fromY)->getColor();
    if (jumpedPiece->getColor() == color) {
        return false;
    }
    return true;
}



  
    
