
#include "Checkers.hpp"
#include <Board-Games/Games/Checkers/Pieces/Pawn/CheckersPawn.hpp>

size_t CHECKERS_BOARD_SIZE = 10;
Checkers::Checkers() : BoardGame(CHECKERS_BOARD_SIZE) {
    // Implementation of Checkers constructor
    this->loadTextures();
    this->initializeGame();
}

void Checkers::initializeGame() {
    // Implementation of initializeGame function
    for (size_t i = 0; i < CHECKERS_BOARD_SIZE; i++)
    {
        for (size_t j = 0; j < CHECKERS_BOARD_SIZE; j++)
        {
            if(board[i][j].getIsDark() && i < 4){
                board[i][j].setPiece(new CheckersPawn(i, j, Color::White));
            }
            else if(board[i][j].getIsDark() && i > 5){
                board[i][j].setPiece(new CheckersPawn(i, j, Color::Black));
            }
            else{
                board[i][j].removePiece();
            }
        }
        
    }
}

void Checkers::loadTextures() {
    // Implementation of loadTextures function
    BoardGame::loadTextures();
    std::string textures[] = {
        "assets/Pieces/Checkers/Pawn/white.png",
        "assets/Pieces/Checkers/Pawn/black.png",

    };

    for (std::string texture : textures) {
        sf::Texture tex;
        tex.loadFromFile(texture);
        tex.setSmooth(true);
        this->textures[texture] = tex;
    }
}


bool Checkers::isPathObstructed(int fromX, int fromY, int toX, int toY) {
    if(fromX > toX)
        return board[fromX-1][fromY].hasPiece();
    if(fromX < toX)
        return board[fromX+1][fromY].hasPiece();
    return false;
}

bool Checkers::movePiece(int fromX, int fromY, int toX, int toY) {
    
    //Check if the new position is empty
    if(board[toX][toY].hasPiece()) return false;
    //Check if move is a capture move and if the path is obstructed
    if(board[fromX][fromY].getPiece()->isValidCaptureMove(toX, toY)  && isPathObstructed(fromX, fromY, toX, toY)){
        board[toX][toY].setPiece(board[fromX][fromY].getPiece());
        board[fromX][fromY].removePiece();
        return true;
    }   
    //Check if move is a normal move 
    if(board[fromX][fromY].getPiece()->isValidMove(toX, toY)){
        board[toX][toY].setPiece(board[fromX][fromY].getPiece());
        return true;
    }

    return false;
}
//Override
void Checkers::handleTile(int x, int y) {
        if (selectedTile == nullptr) {
            if (board[x][y].hasPiece()) {
                selectedTile = &board[x][y];
            }
        } else {
            if (movePiece(selectedTile->getX(), selectedTile->getY(), x, y)) {
                selectedTile = nullptr;
                changePlayer();
                std::cout << "Piece moved" << std::endl;
            }
        }
}