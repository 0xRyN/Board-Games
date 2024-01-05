#include "GameView.hpp"

GameView::GameView(BoardGame& game, int width, int height)
    : game(game), state(game.getGameState()),
      window(sf::VideoMode(width, height), "Board Game") {
    game.loadTextures();
}

#include <SFML/Graphics.hpp>
#include <cmath>

void drawArrow(sf::RenderWindow& window, int boardSize, int fromX, int fromY,
               int toX, int toY) {
    // Calculate the size of each tile
    float tileSize = static_cast<float>(window.getSize().x) / boardSize;

    // Convert tile coordinates to pixel coordinates
    float pixelFromX = fromX * tileSize + tileSize / 2;
    float pixelFromY = fromY * tileSize + tileSize / 2;
    float pixelToX = toX * tileSize + tileSize / 2;
    float pixelToY = toY * tileSize + tileSize / 2;

    sf::Vertex line[] = {
        sf::Vertex(sf::Vector2f(pixelFromX, pixelFromY), sf::Color::Red),
        sf::Vertex(sf::Vector2f(pixelToX, pixelToY), sf::Color::Red)};

    // Draw the line
    window.draw(line, 2, sf::Lines);

    // Calculate the direction of the arrow
    sf::Vector2f direction =
        sf::Vector2f(pixelToX - pixelFromX, pixelToY - pixelFromY);
    float length = sqrt(direction.x * direction.x + direction.y * direction.y);
    direction.x /= length;
    direction.y /= length;

    // Calculate the orthogonal direction
    sf::Vector2f ortho(-direction.y, direction.x);

    // Draw the arrow head
    sf::Vertex arrowHead[] = {
        sf::Vertex(sf::Vector2f(pixelToX, pixelToY), sf::Color::Red),
        sf::Vertex(
            sf::Vector2f(pixelToX - direction.x * 10.0f + ortho.x * 5.0f,
                         pixelToY - direction.y * 10.0f + ortho.y * 5.0f),
            sf::Color::Red),
        sf::Vertex(
            sf::Vector2f(pixelToX - direction.x * 10.0f - ortho.x * 5.0f,
                         pixelToY - direction.y * 10.0f - ortho.y * 5.0f),
            sf::Color::Red)};

    // Draw the arrow head
    window.draw(arrowHead, 3, sf::Triangles);
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
    //  << "Selecting tile (" << x << ", " << y << ")" << std::endl;
    if (!selectedTile) {
        if (state->getTileAt(x, y).hasPiece()) {
            selectedTile = &(state->getTileAt(x, y));
        }
        return;
    }
    const Piece* piece = selectedTile->getPiece();
    // auto moves = piece->getAllAvailableMoves(*state);

    if (piece->getColor() != state->getCurrentPlayer()->getColor()) {
        selectedTile = nullptr;
        return;
    }

    Move move = {piece->getX(), piece->getY(), x, y, false};
    game.handleTurn(move);

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

void GameView::drawArrows() {
    bool ONLY_DRAW_SELECTED_PIECE = false; // TRY FALSE
    auto availableMoves = state->getAvailableMoves();

    if (ONLY_DRAW_SELECTED_PIECE) {
        if (selectedTile) {
            auto pair =
                std::make_pair(selectedTile->getX(), selectedTile->getY());
            auto it = availableMoves.find(pair);
            if (it != availableMoves.end()) {
                for (auto move : it->second) {
                    drawArrow(window, state->getBoardSize(), move.fromX,
                              move.fromY, move.toX, move.toY);
                }
            }
        }
    } else {
        for (auto pair : availableMoves) {
            for (auto move : pair.second) {
                drawArrow(window, state->getBoardSize(), move.fromX, move.fromY,
                          move.toX, move.toY);
            }
        }
    }
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

    // Draw the available moves
    drawArrows();
}

// get the position of the click
void GameView::handleClick() {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    int boardSize = state->getBoardSize();
    int x = mousePos.x / (window.getSize().x / boardSize);
    int y = mousePos.y / (window.getSize().y / boardSize);
    this->selectTile(x, y);
}
