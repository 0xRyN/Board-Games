#include "CheckersGame.hpp"
#include "CheckersGameState.hpp"
#include "CheckersRules.hpp"

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

std::vector<std::pair<int, int>>CheckersGame::getAvailableActions(const BoardGame& game, int x, int y) {
    std::vector<std::pair<int, int>> actions;
    // Get the color of the piece
    Color color = game.getPieceAt(x, y)->getColor();

    // Définir des constantes pour les directions
    const int WHITE_DIRECTION = 1;
    const int BLACK_DIRECTION = -1;

    // Utiliser les constantes dans le code
    int direction = (color == Color::White) ? WHITE_DIRECTION : BLACK_DIRECTION;

    // Iterate through all possible moves in the valid direction
    for (int dx = -1; dx <= 1; dx++) {
        int toX = x + dx;
        int toY = y + direction;

        // Check if the move is within the board boundaries
        if (gameRules->isValidMove(game, x, y, toX, toY)) {
            // Check if the move is valid or a capture
                actions.emplace_back(toX, toY);
            }
        }

    return actions;
}

//function to get available capture moves

std::vector<std::pair<int, int>> CheckersGame::getAvailableCaptureMoves(const BoardGame& game, int x, int y) {
    std::vector<std::pair<int, int>> captures;
    std::vector<std::pair<int, int>> actions = getAvailableActions(game, x, y);
    for (auto action : actions) {
        int toX = action.first;
        int toY = action.second;
        if (gameRules->isValidCaptureMove(game, x, y, toX, toY)) {
            captures.emplace_back(toX, toY);
        }
    }
    return captures;
}

void CheckersGame::setAvailableCaptureMoves(const BoardGame& game, int x, int y) {
    std::vector<std::pair<int, int>> captures = getAvailableCaptureMoves(game, x, y);
        gameState->setAvailableCaptureMoves(captures);
}













