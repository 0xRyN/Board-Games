#include "BoardGame.hpp"



BoardGame::BoardGame(int boardSize)
    : boadSize(boardSize), firstPlayer(Player("Rayan", Color::White)),
      secondPlayer("Ilyas", Color::Black), currentPlayer(&firstPlayer),
      selectedTile(nullptr) {
    for (int i = 0; i < boadSize; ++i) {
        std::vector<Tile> row;
        for (int j = 0; j < boadSize; ++j) {
            row.push_back(Tile((i + j) % 2 == 1, i, j));
        }
        board.push_back(row);
    }

    this->loadTextures();
}

BoardGame::~BoardGame() {
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

int BoardGame::getBoardSize() const {
    return boadSize;
}

const std::map<std::string, sf::Texture>& BoardGame::getTextures() const {
    return textures;
}

Piece* BoardGame::getPieceAt(int x, int y) const {
    return board[x][y].getPiece();
}

const std::vector<std::vector<Tile>>& BoardGame::getBoard() const {
    return board;
}

void BoardGame::selectTile(int x, int y) {
    // Si la case est vide, retournez
    if (isEmpty(x, y)) {
        return;
    }

    // Si la case contient une pièce de l'adversaire, retournez
    if (board[x][y].getPiece()->getColor() != currentPlayer->getColor()) {
        return;
    }

    // Si aucune case n'a été sélectionnée précédemment
    if (!selectedTile) {
        selectedTile = &board[x][y];
    } else {
        // Une case a été sélectionnée précédemment, donc le joueur essaie de faire un mouvement
        Piece* piece = selectedTile->getPiece();

        // Vérifiez si le mouvement est valide
        if (gameRules->isValidMove(*this ,piece->getX(), piece->getY(), x, y)) {
            // Faites le mouvement
            movePiece(piece->getX(), piece->getY(), x, y);

            // Changez le joueur actuel
            changePlayer();
        }

        // Réinitialisez la case sélectionnée
        selectedTile = nullptr;
    }
}



void BoardGame::updatePosition(int fromX, int fromY, int toX, int toY) {
    Piece* piece = board[fromX][fromY].getPiece();
    board[toX][toY].setPiece(piece);
    board[fromX][fromY].setPiece(nullptr);
    piece->setPosition(toX, toY);
}

bool BoardGame::isEmpty(int x, int y) const {
    return !board[x][y].hasPiece();
}

void BoardGame::movePiece(int fromX, int fromY, int toX, int toY) {
    Piece* piece = board[fromX][fromY].getPiece();
    board[toX][toY].setPiece(piece);
    board[fromX][fromY].setPiece(nullptr);
    piece->setPosition(toX, toY);
}

void BoardGame::changePlayer() {
    currentPlayer = (currentPlayer != &firstPlayer) ? &firstPlayer : &secondPlayer;
}








/* void BoardGame::selectTile(int x, int y) {
    if (!selectedTile) {
        if (board[x][y].hasPiece()) {
            selectedTile = &board[x][y];
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


void BoardGame::updatePosition(int fromX, int fromY, int toX, int toY) {
    Piece* piece = board[fromX][fromY].getPiece();
    board[toX][toY].setPiece(piece);
    board[fromX][fromY].setPiece(nullptr);
    piece->setPosition(toX, toY);
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



// Return const reference to avoid copying the map
const std::map<std::string, sf::Texture>& BoardGame::getTextures() const {
    return textures;
}

Piece* BoardGame::getPieceAt(int x, int y) const {
    return board[x][y].getPiece();
}

const std::vector<std::vector<Tile>>& BoardGame::getBoard() const {
    return board;
}

void BoardGame::changePlayer() {
    currentPlayer =
        currentPlayer == &firstPlayer ? &secondPlayer : &firstPlayer;
}

bool BoardGame::isEmpty(int x, int y) const {
    return !board[x][y].hasPiece();
}

void BoardGame::movePiece(int fromX, int fromY, int toX, int toY) {
    Piece* piece = board[fromX][fromY].getPiece();
    board[toX][toY].setPiece(piece);
    board[fromX][fromY].setPiece(nullptr);
    piece->setPosition(toX, toY);
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
 */
