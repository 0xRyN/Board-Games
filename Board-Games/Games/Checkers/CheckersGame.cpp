#include "CheckersGame.hpp"
#include "CheckersGameState.hpp"
#include "CheckersRules.hpp"
#include "CheckersPawn.hpp"

CheckersGame::CheckersGame() : BoardGame(8) {
    gameState = std::make_unique<CheckersGameState>();
    gameRules = std::make_unique<CheckersRules>();
}

CheckersGame::~CheckersGame() {
}


void CheckersGame::loadTextures() {
    // Implementation of loadTextures function
    BoardGame::loadTextures();
    std::string textures[] = {
        "assets/Pieces/Checkers/Pawn/white.png",
        "assets/Pieces/Checkers/Pawn/black.png",
    };
};

void CheckersGame::initializeGame() {
    // Implementation of initializeGame function
    for (int i = 0; i < boadSize; ++i) {
        for (int j = 0; j < boadSize; ++j) {
            if (i < 3 && (i + j) % 2 == 1) {
                board[i][j].setPiece(new CheckersPawn(i, j, Color::White));
            } else if (i > 4 && (i + j) % 2 == 1) {
                board[i][j].setPiece(new CheckersPawn(i, j, Color::Black));
            }
        }
    }
}

void CheckersGame::removeCapturedPiece(int fromX, int fromY, int toX, int toY) {
    int x = fromX, y = fromY;
    int dx = toX - fromX, dy = toY - fromY;
    int steps = std::max(std::abs(dx), std::abs(dy));
    dx /= steps;
    dy /= steps;

    for (int i = 0; i < steps; ++i) {
        x += dx;
        y += dy;
        if (board[x][y].hasPiece()) {
            board[x][y].removePiece();
            std::cout << "Piece captured at (" << x << ", " << y << ")"
                      << std::endl;
            return;
        }
    }
}


//function to get available capture moves



void CheckersGame::setAvailableCaptureMoves(int x, int y) {
    std::vector<std::pair<int, int>> captures = gameRules->getAvailableCaptureMoves(*this, x, y);
        gameState->setAvailableCaptureMoves(captures);
}

void CheckersGame::setRecheableTile(int x, int y) {
    std::vector<std::pair<int, int>> actions = gameRules->getAvailableActions(*this, x, y);
    for (auto action : actions) {
        int toX = action.first;
        int toY = action.second;
         board[toX][toY].setReachable(true);
    }
}













