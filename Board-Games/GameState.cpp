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

void GameState::changePlayer() {
    currentPlayer =
        currentPlayer == &firstPlayer ? &secondPlayer : &firstPlayer;
}

bool GameState::updatePosition(Move move) {
    auto fromX = move.fromX;
    auto fromY = move.fromY;
    auto toX = move.toX;
    auto toY = move.toY;
    Piece* piece = board[fromX][fromY].getPiece();
    board[toX][toY].setPiece(piece);
    board[fromX][fromY].setPiece(nullptr);
    piece->setPosition(toX, toY);

    return true;
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
}

bool GameState::movePiece(Move move) {
    auto fromX = move.fromX;
    auto fromY = move.fromY;
    auto toX = move.toX;
    auto toY = move.toY;

    Piece* piece = board[fromX][fromY].getPiece();
    if (piece == nullptr) {
        return false;
    }

    if (piece->getColor() != currentPlayer->getColor()) {
        return false;
    }

    auto possibleMoves = availableMoves[std::make_pair(fromX, fromY)];

    bool canMove = std::find(possibleMoves.begin(), possibleMoves.end(),
                             move) != possibleMoves.end();

    if (!canMove) {
        return false;
    }

    return true;
}
