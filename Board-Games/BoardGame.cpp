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

std::vector<PossibleMove> BoardGame::computeAllPossibleMoves(int x, int y) {
    std::vector<PossibleMove> moves;
    Piece* piece = board[x][y].getPiece();
    if (piece == nullptr) {
        return moves;
    }

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; j++) {
            if (piece->canMove(i, j) /* && this->isPathClear(x, y, i, j) */) {        //NOTE: canMove() vérifie seulement si le mouvement est valide, pas si le chemin est libre
                moves.push_back({i, j, false});
                std::cout << "Possible move at (" << i << ", " << j << ")"
                          << std::endl;
            } else if (piece->canCapture(i, j) && !this->isPathClear(x, y, i, j) && !board[i][j].hasPiece()) {
                moves.push_back({i, j, true});
                std::cout << "Possible capture at (" << i << ", " << j << ")"
                          << std::endl;
            }
        }
    }

    return moves;
}

bool BoardGame::movePiece(int fromX, int fromY, int toX, int toY) {
    Piece* piece = board[fromX][fromY].getPiece();

    if (piece == nullptr) {
        return false;
    }

    // Check if a capture is possible
    std::vector<PossibleMove> possibleMoves =
        computeAllPossibleMoves(fromX, fromY);

    for (PossibleMove move : possibleMoves) {
        if (move.isCapture) {
            if (move.x == toX && move.y == toY) {
                updatePosition(fromX, fromY, toX, toY);
                removeCapturedPiece(fromX, fromY, toX, toY);
                possibleMoves = computeAllPossibleMoves(toX, toY);
                if (possibleMoves.size() == 0) {
                    changePlayer();
                }
                return true;
            }
            // If a capture is possible, the player must capture
            return false;
        }
    }

    // If the path is clear, call canMove
    if (isPathClear(fromX, fromY, toX, toY)) {
        if (piece->canMove(toX, toY)) {
            updatePosition(fromX, fromY, toX, toY);
            changePlayer();
            return true;
        }
    }
    return false;
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