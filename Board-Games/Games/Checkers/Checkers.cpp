
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
    for (size_t i = 0; i < CHECKERS_BOARD_SIZE; i++) {
        for (size_t j = 0; j < CHECKERS_BOARD_SIZE; j++) {
            if (board[i][j].getIsDark() && j < 4) {
                board[i][j].setPiece(new CheckersPawn(i, j, Color::White));
            } else if (board[i][j].getIsDark() && j > 5) {
                board[i][j].setPiece(new CheckersPawn(i, j, Color::Black));
            } else {
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
    if (fromX > toX)
        return board[fromX - 1][fromY].hasPiece();
    if (fromX < toX)
        return board[fromX + 1][fromY].hasPiece();
    return false;
}

bool Checkers::movePiece(int fromX, int fromY, int toX, int toY) {
    // Check if the new position is empty
    if (board[toX][toY].hasPiece()){
        return false;
    }
    Piece* piece = board[fromX][fromY].getPiece();
    if (piece == nullptr) {
        return false;
    }
    
    // Check if move is a capture move and if the path is obstructed
    if (piece->isValidCaptureMove(toX, toY) && isPathObstructed(fromX, fromY, toX, toY)) {
        board[toX][toY].setPiece(piece);
        return true;
    }
    // Check if move is a normal move
    if (piece->isValidMove(toX, toY)) {
        board[toX][toY].setPiece(piece);
        board[fromX][fromY].setPiece(nullptr);
        piece->setPosition(toX, toY);

        return true;
    }

    return false;
}
// Override
void Checkers::handleTile(int x, int y) {
    // Implementation of handleTile function
    
    if(selectedTile == nullptr && board[x][y].hasPiece()){
        selectedTile = &board[x][y];
    }
    else if(selectedTile != nullptr){
        if(movePiece(selectedTile->getPiece()->getX(), selectedTile->getPiece()->getY(), x, y)){
            changePlayer();
        }
        selectedTile = nullptr;
    }


}


