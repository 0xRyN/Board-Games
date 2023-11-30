
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


bool Checkers::movePiece(int fromX, int fromY, int toX, int toY) {
    // Check if the new position is empty
    if (board[toX][toY].hasPiece()){
        return false;
    }
    
    Piece* piece = board[fromX][fromY].getPiece();

    // Check if move is a capture move and if it is, remove the piece in the middle
    if (piece->isValidCaptureMove(toX, toY)) {
        int midX = (fromX + toX) / 2;
        int midY = (fromY + toY) / 2;
        if (!board[midX][midY].hasPiece() || board[midX][midY].getPiece()->getColor() == piece->getColor()) {
            return false;
        }
        board[midX][midY].removePiece();
        updatePosition(fromX, fromY, toX, toY);
        return true;
    }
    // Check if move is a normal move
    else if (piece->isValidMove(toX, toY)) {
        updatePosition(fromX, fromY, toX, toY);
        return true;
    }

    return false;
}

void Checkers::updatePosition(int fromX, int fromY, int toX, int toY) {
    // Implementation of updatePosition function
        Piece* piece = board[fromX][fromY].getPiece();
        board[toX][toY].setPiece(piece);
        board[fromX][fromY].setPiece(nullptr);
        piece->setPosition(toX, toY);
}

// Override
void Checkers::selection(int x, int y) {
    // Implementation of handleTile function
    if(selectedTile == nullptr && board[x][y].hasPiece()){
        selectedTile = &board[x][y];
    }
    else if(selectedTile != nullptr){
        Piece* piece = selectedTile->getPiece();
        if(piece->colorToInt() != this->playerToInt()){
            selectedTile = nullptr;
            return;
        }
        if(movePiece(piece->getX(), piece->getY(), x, y)){
            changePlayer();
        }
        selectedTile = nullptr;
    }


}


