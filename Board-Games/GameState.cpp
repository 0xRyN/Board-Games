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

void GameState::setForcedMoves(std::vector<Move> forcedMoves) {
    this->forcedMoves = forcedMoves;
}

void GameState::changePlayer() {
    currentPlayer =
        currentPlayer == &firstPlayer ? &secondPlayer : &firstPlayer;
}

bool GameState::updatePosition(Move move, bool isCapture) {
    auto fromX = move.fromX;
    auto fromY = move.fromY;
    auto toX = move.toX;
    auto toY = move.toY;
    std::cout << "Moving from (" << fromX << ", " << fromY << ") to (" << toX
              << ", " << toY << ")" << std::endl;
    Piece* piece = board[fromX][fromY].getPiece();
    board[toX][toY].setPiece(piece);
    board[fromX][fromY].setPiece(nullptr);
    piece->setPosition(toX, toY);
    if (isCapture) {
        removeCapturedPiece((fromX + toX) / 2, (fromY + toY) / 2);
    }

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



bool GameState::movePiece(Move move) {
    // We have forced moves and the current move is not one of them
    //show the forced moves

    if (!forcedMoves.empty() &&
        std::find(forcedMoves.begin(), forcedMoves.end(), move) ==
            forcedMoves.end()) {
        return false;
    }

    auto fromX = move.fromX;
    auto fromY = move.fromY;
    auto toX = move.toX;
    auto toY = move.toY;
    Piece* piece = board[fromX][fromY].getPiece();

    if (piece == nullptr) {
        return false;
    }

    auto step = 0;
    if (piece->canCapture(*this, toX, toY)) {
        step = 2;
    } else if (piece->canMove(*this, toX, toY)) {
        step = 1;
    } else {
        return false;
    }
    
    updatePosition(move, step == 2);


    return true;
}
