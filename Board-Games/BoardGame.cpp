#include "BoardGame.hpp"
#include "GameState.hpp"

void BoardGame::selectTile(int x, int y) {
    if (!selectedTile) {
        if (board[x][y].hasPiece()) {
            selectedTile = &board[x][y];
            computeAllPossibleMoves(x, y);
        }
        return;
    }

    Piece* piece = selectedTile->getPiece();
    if (piece->getColor() != currentPlayer->getColor()) {
        selectedTile = nullptr;
        return;
    }

    movePiece(piece->getX(), piece->getY(), x, y);
    selectedTile = nullptr;
}

bool BoardGame::isPathClear(int fromX, int fromY, int toX, int toY) const {
    int x = fromX, y = fromY;
    int dx = toX - fromX, dy = toY - fromY;
    int steps = std::max(std::abs(dx), std::abs(dy));
    dx /= steps;
    dy /= steps;

    for (int i = 0; i < steps; ++i) {
        x += dx;
        y += dy;
        if (board[x][y].hasPiece()) {
            return false;
        }
    }

    return true;
}

void BoardGame::updatePosition(int fromX, int fromY, int toX, int toY) {
    Piece* piece = board[fromX][fromY].getPiece();
    board[toX][toY].setPiece(piece);
    board[fromX][fromY].setPiece(nullptr);
    piece->setPosition(toX, toY);
}

void BoardGame::removeCapturedPiece(int fromX, int fromY, int toX, int toY) {
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

BoardGame::BoardGame(int boardSize)
    : size(boardSize), firstPlayer(Player("Rayan", Color::White)),
      secondPlayer("Ilyas", Color::Black), currentPlayer(&firstPlayer),
      selectedTile(nullptr) {
    for (int i = 0; i < size; ++i) {
        std::vector<Tile> row;
        for (int j = 0; j < size; ++j) {
            row.push_back(Tile((i + j) % 2 == 1, i, j));
        }
        board.push_back(row);
    }

    this->loadTextures();
}

int BoardGame::getBoardSize() const {
    return size;
}

const std::vector<std::vector<Tile>>& BoardGame::getBoard() const {
    return board;
}

// Return const reference to avoid copying the map
const std::map<std::string, sf::Texture>& BoardGame::getTextures() const {
    return textures;
}

Piece* BoardGame::getPieceAt(int x, int y) const {
    return board[x][y].getPiece();
}

void BoardGame::displayBoard() {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            std::cout << (board[i][j].getIsDark() ? "X " : "O ");
        }
    }
}

void BoardGame::changePlayer() {
    currentPlayer =
        currentPlayer == &firstPlayer ? &secondPlayer : &firstPlayer;
}

void BoardGame::movePiece(int fromX, int fromY, int toX, int toY) {
    if (gameRules->isValidMove(*this, fromX, fromY, toX, toY)) {
        // Execute the move
        // ...

        std::vector<std::pair<int, int>> actions =
            gameRules->getAvailableActions(*this, toX, toY);
        if (!actions.empty()) {
            gameState->startActionSequence();
            // Handle available actions
        } else {
            gameState->endActionSequence();
            // Change player, or other end-of-turn logic
        }
    }
}

void BoardGame::loadTextures() {
    std::string textures[] = {
        "assets/Tiles/dark.png",
        "assets/Tiles/light.png",
    };

    for (std::string texture : textures) {
        sf::Texture tex;
        tex.loadFromFile(texture);
        tex.setSmooth(true);
        this->textures[texture] = tex;
    }
}

GameState* BoardGame::getGameState() const {
    return gameState;
}