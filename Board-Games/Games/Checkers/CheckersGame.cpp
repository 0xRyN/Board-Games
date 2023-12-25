#include "CheckersGame.hpp"
#include "CheckersGameState.hpp"
#include "CheckersRules.hpp"
#include "CheckersPawn.hpp"

//define a constant for the number of rows and columns
#define BOARD_SIZE 8

CheckersGame::CheckersGame() : BoardGame() {
    //TODO: Remove make unique 
    gameState = std::make_unique<CheckersGameState>();
    gameState->setBoardSize(BOARD_SIZE);
    gameState->createBoard();
    gameState->initializeGame();
}








/*
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
} */















