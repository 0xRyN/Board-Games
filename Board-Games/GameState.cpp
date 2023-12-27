#include "GameState.hpp"

#include <algorithm>

GameState::GameState(int boardSize)
    : boardSize(boardSize), firstPlayer(Player("Player 1", Color::White)),
      secondPlayer(Player("Player 2", Color::Black)),
      currentPlayer(&firstPlayer) {

    // Initialize empty board
    for (int i = 0; i < boardSize; ++i) {
        std::vector<Tile> row;
        for (int j = 0; j < boardSize; ++j) {
            row.push_back(Tile((i + j) % 2 == 1, i, j));
        }
        board.push_back(row);
    }
}

GameState::~GameState() {
}

int GameState::getBoardSize() const {
    return boardSize;
}

const std::vector<std::vector<Tile>>& GameState::getBoard() const {
    return board;
}

const Tile& GameState::getTileAt(int x, int y) const {
    // Check if the coordinates are valid
    if (x < 0 || x >= boardSize || y < 0 || y >= boardSize) {
        throw std::invalid_argument("Invalid coordinates");
    }
    return board[x][y];
}

const Player* GameState::getCurrentPlayer() const {
    return currentPlayer;
}

const std::map<std::pair<int, int>, std::vector<Move>>&
GameState::getAvailableMoves() const {
    return availableMoves;
}

const void GameState::setAvailableMoves(
    std::map<std::pair<int, int>, std::vector<Move>>& availableMoves) {
    this->availableMoves = availableMoves;
}

void GameState::changePlayer() {
    currentPlayer =
        currentPlayer == &firstPlayer ? &secondPlayer : &firstPlayer;
}

bool GameState::removeCapturedPiece(Move move) {
    auto x = (move.fromX + move.toX) / 2;
    auto y = (move.fromY + move.toY) / 2;

    Piece* piece = board[x][y].getPiece();
    if (piece == nullptr) {
        return false;
    }

    board[x][y].removePiece();
    return true;
}

void GameState::initializeGame() {
}

void GameState::eraseNoCaptureMoves() {
    std::map<std::pair<int, int>, std::vector<Move>> captureMoves;
    bool hasCaptureMove = false;

    for (auto& pair : availableMoves) {
        std::vector<Move> temp;
        for (auto& move : pair.second) {
            if (move.isCaptureMove) {
                temp.push_back(move);
                std::cout << "Has capture move : " << move << std::endl;
                hasCaptureMove = true;
            }
        }
        if (!temp.empty()) {
            captureMoves[pair.first] = temp;
        }
    }

    if (hasCaptureMove) {
        availableMoves = captureMoves;
    }
}

void GameState::computeAvailableMoves() {
    // TODO: Only check pieces of the current player
    availableMoves.clear();
    for (int i = 0; i < boardSize; ++i) {
        for (int j = 0; j < boardSize; j++) {
            Piece* piece = board[i][j].getPiece();
            if (piece != nullptr &&
                piece->getColor() == currentPlayer->getColor()) {
                auto moves = piece->getAllAvailableMoves(*this);
                std::vector<Move> copy = *moves;
                delete moves;
                availableMoves[std::make_pair(i, j)] = copy;
            }
        }
    }

    eraseNoCaptureMoves();

    std::cout << "Current turn : " << currentPlayer->getName() << std::endl;
    std::cout << "Available moves: " << std::endl;
    for (auto& pair : availableMoves) {
        for (auto& move : pair.second) {
            std::cout << move << std::endl;
        }
    }
}

void GameState::movePiece(Move move) {
    Piece* piece = board[move.fromX][move.fromY].getPiece();
    board[move.toX][move.toY].setPiece(piece);
    board[move.fromX][move.fromY].setPiece(nullptr);
    piece->setPosition(move.toX, move.toY);
    if (move.isCaptureMove) {
        removeCapturedPiece(move);
    }
}
