#include "GameState.hpp"

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

bool GameState::movePiece(Move move) {
    auto fromX = move.fromX;
    auto fromY = move.fromY;
    auto toX = move.toX;
    auto toY = move.toY;
    Piece* piece = board[fromX][fromY].getPiece();

    if (piece == nullptr) {
        return false;
    }

    if (!piece->isValidMove(*this, toX, toY)) {
        std::cout << "Invalid move" << std::endl;
        return false;
    }

    return true;
}
