#include "CheckersQueen.hpp"

#include <iostream>

CheckersQueen::CheckersQueen(int posX, int posY, Color pieceColor)
    : Piece(posX, posY, pieceColor) {
    texturePath = (pieceColor == Color::White)
                      ? "assets/Pieces/Checkers/Queen/light.png"
                      : "assets/Pieces/Checkers/Queen/dark.png";
}

bool isWithinBounds(int x, int y, int boardSize) {
    if (x < 0 || x >= boardSize || y < 0 || y >= boardSize) {
        return false;
    }
    return true;
}

bool CheckersQueen::canCapture(GameState& state, int toX, int toY) const {
    return false;
}

bool CheckersQueen::canMove(GameState& state, int toX, int toY) const {
    return false;
}

void CheckersQueen::findAllMoves(
    GameState& state, int x, int y, std::vector<Move>& moves,
    std::vector<Move>& path, std::vector<std::vector<bool>>& visited) const {

    std::cout << "Initial position: (" << x << ", " << y << ")" << std::endl;
    bool captureMade = false;
    static const int dirs[4][2] = {{1, 1}, {1, -1}, {-1, -1}, {-1, 1}};

    for (const auto& dir : dirs) {
        int nextX = x + dir[0];
        int nextY = y + dir[1];

        if (isWithinBounds(nextX, nextY, state.getBoardSize()) &&
            !visited[nextX][nextY]) {
            Piece* nextPiece = state.getTileAt(nextX, nextY).getPiece();
            if (nextPiece && nextPiece->getColor() != color) {
                int jumpX = nextX + dir[0];
                int jumpY = nextY + dir[1];
                if (isWithinBounds(jumpX, jumpY, state.getBoardSize()) &&
                    !state.getTileAt(jumpX, jumpY).getPiece()) {
                    // Perform capture
                    visited[nextX][nextY] = true;
                    path.push_back(Move(x, y, jumpX, jumpY, true));
                    findAllMoves(state, jumpX, jumpY, moves, path, visited);
                    path.pop_back();
                    visited[nextX][nextY] = false;
                    captureMade = true;
                }
            }
        }
    }

    if (!captureMade && !path.empty()) {
        // If no further capture and path is not empty, consider this path as a
        // valid move sequence
        moves.insert(moves.end(), path.begin(), path.end());
    }
}

const std::vector<Move>*
CheckersQueen::getAllAvailableMoves(GameState& state) const {
    std::vector<Move>* moves = new std::vector<Move>();
    std::vector<Move> path;
    std::vector<std::vector<bool>> visited(
        state.getBoardSize(), std::vector<bool>(state.getBoardSize(), false));

    findAllMoves(state, x, y, *moves, path, visited);

    return moves;
}
