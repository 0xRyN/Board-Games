
#include "Checkers.hpp"
#include "Pieces/Pawn.hpp" 

int CHECKERS_BOARD_SIZE = 8;

Checkers::Checkers() : BoardGame(CHECKERS_BOARD_SIZE) {
    // Implementation of Checkers constructor
}

void Checkers::initializeGame() {
    // iniatialization of the board
    for (size_t i = 0; i < CHECKERS_BOARD_SIZE; i++)
    {
        for (size_t j = 0; j < CHECKERS_BOARD_SIZE; j++)
        {
            if(board[i][j].isDarkTile() && i < 3){
                board[i][j].setPiece(new Pawn(i, j, Color::White));
            }
            else if(board[i][j].isDarkTile() && i > 4){
                board[i][j].setPiece(new Pawn(i, j, Color::Black));
            }
            else{
                board[i][j].removePiece();
            }
        }
        
    }
    
}

bool Checkers::movePiece(int fromX, int fromY, int toX, int toY) {
    // Implementation of movePiece function


    return false;
}
