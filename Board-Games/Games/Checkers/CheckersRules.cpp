#include "CheckersRules.hpp"

bool CheckersRules::isValidMove(const BoardGame& game, int fromX, int fromY,
                                int toX, int toY) const {
    // check if the move is diagonal
    if (!isMoveDiagonal(fromX, fromY, toX, toY)) {
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
}

bool CheckersRules::isCaptureMove(const BoardGame& game, int fromX, int fromY,
                                  int toX, int toY) const {
    // Check if the move is diagonal and of length 2
    if (abs(fromX - toX) != 2 || abs(fromY - toY) != 2) {
        return false;
    }

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

    // Check if the destination square is empty
    if (game.getPieceAt(toX, toY) != nullptr) {
        return false;
    }

    return true;
}

std::vector<std::pair<int, int>>
CheckersRules::getAvailableActions(const BoardGame& game, int x, int y) {
    std::vector<std::pair<int, int>> actions;
    // Get the color of the piece
    Color color = game.getPieceAt(x, y)->getColor();

    // Determine the direction of movement based on the color
    int direction = (color == Color::White) ? 1 : -1;

    // Iterate through all possible moves in the valid direction
    for (int dx = -1; dx <= 1; dx++) {
        int toX = x + dx;
        int toY = y + direction;

        // Check if the move is within the board boundaries and is valid
        if (isWithinBoard(game, toX, toY) &&
            isValidMove(game, x, y, toX, toY)) {
            actions.emplace_back(toX, toY);
        }

        // Check if the move is within the board boundaries and is valid or a
        // capture
        if (isWithinBoard(game, toX, toY) &&
            (isValidMove(game, x, y, toX, toY) ||
             isCaptureMove(game, x, y, toX, toY))) {
            actions.emplace_back(toX, toY);
        }
    }

    return actions;
}

bool CheckersRules::isMoveDiagonal(int fromX, int fromY, int toX,
                                   int toY) const {
    return abs(fromX - toX) == abs(fromY - toY);
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

bool CheckersRules::isWithinBoard(const BoardGame& game, int x, int y) const {
    return x >= 0 && x < game.getBoardSize() && y >= 0 &&
           y < game.getBoardSize();
}
