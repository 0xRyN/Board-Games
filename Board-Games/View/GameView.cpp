#include "GameView.hpp"

GameView::GameView(BoardGame& game, int width, int height)
    : game(game), window(sf::VideoMode(width, height), "Board Game") {
}

void GameView::run() {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            // Gérer d'autres événements ici, comme les clics de souris
        }

        window.clear(sf::Color::White);
        drawBoard();
        // Appeler les méthodes de dessin des pièces ici
        window.display();
    }
}

void GameView::drawPiece(Piece* piece, int x, int y, int tileSize) {
    // Dessiner une pièce à la position (x, y)
    auto texturePath = piece->getTexturePath();
    auto texture = game.getTextures().at(texturePath);
    sf::Sprite sprite(texture);
    sprite.setPosition(x, y);
    sprite.setScale(0.1, 0.1);
    window.draw(sprite);
}

void GameView::drawBoard() {
    // Draw a 2D Board
    auto size = window.getSize();
    int width = size.x;
    int height = size.y;
    int boardSize = game.getBoardSize();
    int tileSize = std::min(width, height) / boardSize;

    for (int i = 0; i < boardSize; ++i) {
        for (int j = i % 2; j < boardSize; j += 2) {
            sf::RectangleShape tile(sf::Vector2f(tileSize, tileSize));
            tile.setPosition(j * tileSize, i * tileSize);
            tile.setFillColor(sf::Color::Black);
            window.draw(tile);

            // Draw a piece if there is one
            auto piece = game.getPieceAt(i, j);
            if (piece != nullptr) {
                drawPiece(piece, j * tileSize, i * tileSize, tileSize);
            }
        }
    }
}
