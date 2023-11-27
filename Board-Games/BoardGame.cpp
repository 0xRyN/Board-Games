#include "BoardGame.hpp"


Player Player1("Player 1", sf::Color::White);
Player Player2("Player 2", sf::Color::Black);

BoardGame::BoardGame(int boardSize)
    : size(boardSize), currentPlayer(Player1), selectedTile(nullptr) {
    for (int i = 0; i < size; ++i) {
       
        std::vector<Tile> row;
        for (int j = 0; j < size; ++j) {
            row.push_back(Tile((i + j) % 2 == 1));
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
        std::cout << std::endl;
    }
}

void BoardGame::changePlayer() {
    currentPlayer = currentPlayer.getName() == Player1.getName() ? Player2 : Player1;
}

bool BoardGame::movePiece(int fromX, int fromY, int toX, int toY) {
    return false;
}

void BoardGame::handleEvent(sf::Event event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2i mousePos = sf::Mouse::getPosition();
        int x = mousePos.x / 100;
        int y = mousePos.y / 100;

        if (selectedTile == nullptr) {
            if (board[x][y].hasPiece() &&
                board[x][y].getPiece()->getColor() == currentPlayer.getColor()) {
                selectedTile = &board[x][y];
            }
        } else {
            if (movePiece(selectedTile->getX(), selectedTile->getY(), x, y)) {
                changePlayer();
            }
            selectedTile = nullptr;
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

