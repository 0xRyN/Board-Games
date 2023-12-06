#include "BoardGame.hpp"

bool BoardGame::isPathClear(int fromX, int fromY, int toX, int toY) const {
    int x = fromX, y = fromY;
    int dx = toX - fromX, dy = toY - fromY;
    int steps = std::max(std::abs(dx), std::abs(dy));
    dx /= steps;
    dy /= steps;

    for (int i = 0; i < steps; ++i) {
        x += dx;
        y += dy;
        if (board[x][y].getPiece() != nullptr) {
            return false;
        }
    }

    return true;
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

bool BoardGame::movePiece(int fromX, int fromY, int toX, int toY) {
    Piece* piece = board[fromX][fromY].getPiece();

    if (piece == nullptr) {
        return false;
    }

    // If the path is clear, call canMove
    if (isPathClear(fromX, fromY, toX, toY)) {
        if (piece->canMove(toX, toY)) {
            board[fromX][fromY].setPiece(nullptr);
            board[toX][toY].setPiece(piece);
            return true;
        }
    }

    // Else, call canCapture
    else {
        if (piece->canCapture(toX, toY)) {
            board[fromX][fromY].setPiece(nullptr);
            board[toX][toY].setPiece(piece);
            return true;
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
