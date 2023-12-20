#include "GameView.hpp"

GameView::GameView(BoardGame& game, int width, int height)
    : game(game), state(game.getGameState()),
      window(sf::VideoMode(width, height), "Board Game") {
    game.loadTextures();
}

void GameView::run() {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            // Gérer d'autres événements ici, comme les clics de souris
            if (event.type == sf::Event::MouseButtonPressed) {
                handleClick();
            }
        }

        window.clear(sf::Color::White);
        drawBoard(); // Appeler les méthodes de dessin des pièces ici
        window.display();
    }
}

void GameView::selectTile(int x, int y) {
    if (!selectedTile) {
        if (state->getTileAt(x, y).hasPiece()) {
            selectedTile = &(state->getTileAt(x, y));
        }
        return;
    }

    const Piece* piece = selectedTile->getPiece();
    // // TODO: Implement the use of getAllAvailableMoves like this
    // // getAllAvailableMoves returns all available moves for a piece, and
    // // if needed to, makes them forced (inside Piece::canCapture)

    if (piece->getColor() != state->getCurrentPlayer()->getColor()) {
        selectedTile = nullptr;
        return;
    }

    Move move = {piece->getX(), piece->getY(), x, y, false};

    if (state->movePiece(move)) {
        state->setForcedMoves({});
        state->changePlayer();
        state->getAllAvailableMovesForAllPieces();

    }

    selectedTile = nullptr;
}

void GameView::drawTile(const Tile& tile, int x, int y, int tileSize) {
    // Dessiner une case à la position (x, y)
    auto texturePath = tile.getTexturePath();
    auto texture = game.getTextures().at(texturePath);
    sf::Sprite sprite(texture);
    sprite.setPosition(x, y);
    sprite.setScale((double)tileSize / (double)texture.getSize().x,
                    (double)tileSize / (double)texture.getSize().y);
    window.draw(sprite);
}

void GameView::drawPiece(const Piece* piece, int x, int y, int tileSize) {
    // Dessiner une pièce à la position (x, y)
    auto texturePath = piece->getTexturePath();
    auto texture = game.getTextures().at(texturePath);
    auto desiredSizePixels = tileSize * 0.8;
    auto textureSizePixels = texture.getSize();
    sf::Sprite sprite(texture);

    double desiredWidth =
        (double)desiredSizePixels / (double)textureSizePixels.x;
    double desiredHeight =
        (double)desiredSizePixels / (double)textureSizePixels.y;

    sprite.setScale(desiredWidth, desiredHeight);

    sprite.setPosition(x + (tileSize - desiredSizePixels) / 2,
                       y + (tileSize - desiredSizePixels) / 2);
    window.draw(sprite);
}

void GameView::drawBoard() {
    // Draw a 2D Board
    auto size = window.getSize();
    int width = size.x;
    int height = size.y;
    int boardSize = state->getBoardSize();
    int tileSize = std::min(width, height) / boardSize;

    for (int i = 0; i < boardSize; ++i) {
        for (int j = 0; j < boardSize; ++j) {
            sf::RectangleShape tile(sf::Vector2f(tileSize, tileSize));
            tile.setPosition(i * tileSize, j * tileSize);

            const Tile& tilePtr = state->getTileAt(i, j);
            drawTile(tilePtr, i * tileSize, j * tileSize, tileSize);

            // Draw a piece if there is one
            const Piece* piece = tilePtr.getPiece();
            if (piece != nullptr) {
                drawPiece(piece, i * tileSize, j * tileSize, tileSize);
            }
        }
    }
}

// get the position of the click
void GameView::handleClick() {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    int boardSize = state->getBoardSize();
    int x = mousePos.x / (window.getSize().x / boardSize);
    int y = mousePos.y / (window.getSize().y / boardSize);
    this->selectTile(x, y);

}
