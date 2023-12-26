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
    return board[x][y];
}

const Player* GameState::getCurrentPlayer() const {
    return currentPlayer;
}

const std::map<std::pair<int, int>, std::vector<Move>>&
GameState::getAvailableMoves() const {
    return availableMoves;
}

void GameState::changePlayer() {
    currentPlayer =
        currentPlayer == &firstPlayer ? &secondPlayer : &firstPlayer;
}




bool GameState::removeCapturedPiece(int x, int y) {
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
    //keep only capture moves if there are any
    bool hasCaptureMove = false;
    for (auto it = availableMoves.begin(); it != availableMoves.end();) {
        auto moves = it->second;
        for (auto move : moves) {
            if (move.isCaptureMove) {
                hasCaptureMove = true;
                break;
            }
        }
        if (!hasCaptureMove) {
            it = availableMoves.erase(it);
        } else {
            ++it;
        }
    }
}

void GameState::computeAvailableMoves() {
    // TODO: Only check pieces of the current player
    availableMoves.clear();
    for (int i = 0; i < boardSize; ++i) {
        for (int j = 0; j < boardSize; j++) {
            Piece* piece = board[i][j].getPiece();
            if (piece != nullptr) {
                auto moves = piece->getAllAvailableMoves(*this);
                std::vector<Move> copy = *moves;
                availableMoves[std::make_pair(i, j)] = copy;
            }
        }
    }
    eraseNoCaptureMoves();
}

void GameState::movePiece(Move move) {
    Piece* piece = board[move.fromX][move.fromY].getPiece();
    board[move.toX][move.toY].setPiece(piece);
    board[move.fromX][move.fromY].setPiece(nullptr);
    piece->setPosition(move.toX, move.toY);
    if (move.isCaptureMove) {
        removeCapturedPiece(move.fromX, move.fromY);
    }
}
