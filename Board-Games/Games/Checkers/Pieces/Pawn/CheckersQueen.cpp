#include "CheckersQueen.hpp"

#include <algorithm>
#include <iostream>
#include <unistd.h>

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

std::string dirToString(std::pair<int, int> direction) {
    if (direction.first == 1 && direction.second == 1) {
        return "bas-droite";
    } else if (direction.first == 1 && direction.second == -1) {
        return "haut-droite";
    } else if (direction.first == -1 && direction.second == 1) {
        return "bas-gauche";
    } else if (direction.first == -1 && direction.second == -1) {
        return "haut-gauche";
    }
    return "unknown";
}

// TAKES INTO ACCOUNT CAPTURES, DONT RETURN BEHIND TOO
std::vector<std::pair<int, int>>
getRemainingDirections(std::pair<int, int> dir) {
    std::vector<std::pair<int, int>> remainingDirections;
    if (dir.first == 1 && dir.second == 1) {
        remainingDirections = {{1, -1}, {-1, 1}};
    } else if (dir.first == 1 && dir.second == -1) {
        remainingDirections = {{1, 1}, {-1, -1}};
    } else if (dir.first == -1 && dir.second == 1) {
        remainingDirections = {{1, 1}, {-1, -1}};
    } else if (dir.first == -1 && dir.second == -1) {
        remainingDirections = {{1, -1}, {-1, 1}};
    }
    return remainingDirections;
}

int walkAfterCapture() {
}

void printPath(std::vector<Move>& path) {
    std::cout << "START PATH: " << std::endl;
    for (auto& move : path) {
        std::cout << move << std::endl;
    }
    std::cout << "END PATH" << std::endl;
}

int walkCaptures(GameState& state, int fromX, int fromY,
                 std::pair<int, int> direction, std::vector<Move>& path) {

    std::cout << "Walking in direction: " << dirToString(direction)
              << ", starting at (" << fromX << ", " << fromY << ")"
              << std::endl;

    // printPath(path);

    Color currentColor = state.getCurrentPlayer()->getColor();

    int nextX = fromX;
    int nextY = fromY;
    while (true) {
        // std::cin.get();
        nextX += direction.first;
        nextY += direction.second;

        if (!isWithinBounds(nextX, nextY, state.getBoardSize()))
            return 0;

        Piece* piece = state.getTileAt(nextX, nextY).getPiece();

        // No piece, continue moving.
        if (piece == nullptr)
            continue;

        Color pieceColor = piece->getColor();

        // Allied piece, return 0
        if (pieceColor == currentColor)
            return 0;

        // Enemy piece, check if square after is empty for capture
        else {
            int captureX = nextX + direction.first;
            int captureY = nextY + direction.second;

            // Has a piece, no need to continue further, no captures available
            if (state.getTileAt(captureX, captureY).hasPiece())
                return 0;

            // We found a possible capture, add it to the counter and recurse
            std::cout << "Capture: (" << fromX << ", " << fromY << ")"
                      << "-> (" << captureX << ", " << captureY << ")"
                      << std::endl;

            int max = 0;
            std::vector<Move> maxPath;

            // The walk after the capture
            int captureWalkX = captureX;
            int captureWalkY = captureY;

            int maxCaptureWalkX = captureX;
            int maxCaptureWalkY = captureY;

            while (true) {
                std::cout << "[Capture Walk] (" << captureX << ", " << captureY
                          << ") -> (" << captureWalkX << ", " << captureWalkY
                          << ")" << std::endl;

                // If we are out of bounds, stop
                if (!isWithinBounds(captureWalkX, captureWalkY,
                                    state.getBoardSize()))
                    break;

                // If there is a piece, stop
                Piece* piece =
                    state.getTileAt(captureWalkX, captureWalkY).getPiece();
                if (piece != nullptr)
                    break;

                auto otherDirections = getRemainingDirections(direction);

                // If there is no piece, check for captures in all directions
                for (auto otherDirection : otherDirections) {
                    auto tempPath = std::vector<Move>();
                    int result = walkCaptures(state, captureWalkX, captureWalkY,
                                              otherDirection, tempPath);

                    if (result > max) {
                        std::cout << "[MAX] New max: " << result << std::endl;
                        max = result;
                        maxPath = tempPath;
                        maxCaptureWalkX = captureWalkX;
                        maxCaptureWalkY = captureWalkY;
                    }
                }

                // Continue walking in the same direction
                captureWalkX += direction.first;
                captureWalkY += direction.second;
            }

            path.push_back(
                Move(fromX, fromY, maxCaptureWalkX, maxCaptureWalkY, true));

            // We finished walking after the capture
            path.insert(path.end(), maxPath.begin(), maxPath.end());

            return path.size();
        }
    }

    throw std::runtime_error("Should not reach this point");
}

void CheckersQueen::findMoves(GameState& state, int x, int y, bool initialCall,
                              std::vector<Move>& moves) const {
    // Check for capturing moves first
    // Directions in which a king can move/capture
    std::vector<std::pair<int, int>> directions = {
        {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

    bool captureAvailable = false;
    for (auto& dir : directions) {
        int nx = x, ny = y;
        bool jumpedOverPiece = false;

        while (true) {
            nx += dir.first;
            ny += dir.second;

            if (!isWithinBounds(nx, ny, state.getBoardSize()))
                break; // Check if position is still on the board

            Piece* piece = state.getTileAt(nx, ny).getPiece();
            if (piece != nullptr) {
                if (jumpedOverPiece || piece->getColor() == color)
                    break; // Can't jump over more than one piece or one of the
                           // same color
                jumpedOverPiece = true;
            } else {
                if (jumpedOverPiece) {
                    // Valid capture move found
                    captureAvailable = true;
                    moves.push_back(Move(x, y, nx, ny, true));
                    findMoves(state, nx, ny, false,
                              moves); // Continue searching for more jumps from
                                      // the new position
                } else if (initialCall) {
                    // Non-capture move (only add if no capture has been found
                    // yet)
                    moves.push_back(Move(x, y, nx, ny, false));
                }
            }
        }
    }

    // If any capture moves are available, remove all non-capture moves
    if (captureAvailable) {
        moves.erase(std::remove_if(
                        moves.begin(), moves.end(),
                        [](const Move& move) { return !move.isCaptureMove; }),
                    moves.end());
    }
}

const std::vector<Move>*
CheckersQueen::getAllAvailableMoves(GameState& state) const {
    std::vector<std::pair<int, int>> directions = {
        {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

    std::vector<Move>* path = new std::vector<Move>();

    int max = 0;

    for (auto& dir : directions) {
        auto tempPath = std::vector<Move>();
        int result = walkCaptures(state, x, y, dir, tempPath);

        if (result > max) {
            std::cout << "[MAX] New max: " << result << std::endl;
            max = result;
            *path = tempPath;
        }
    }

    for (auto& move : *path) {
        std::cout << move << std::endl;
    }

    return path;
}
