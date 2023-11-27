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
        
        game.handleEvent(event);
        window.clear(sf::Color::White);
        drawBoard();
        // Appeler les méthodes de dessin des pièces ici
        window.display();
    }
}

void GameView::drawTile(Tile* tile, int x, int y, int tileSize) {
    // Dessiner une case à la position (x, y)
    auto texturePath = tile->getTexturePath();
    auto texture = game.getTextures().at(texturePath);
    sf::Sprite sprite(texture);
    sprite.setPosition(x, y);
    sprite.setScale((double)tileSize / (double)texture.getSize().x,
                    (double)tileSize / (double)texture.getSize().y);
    window.draw(sprite);
}

void GameView::drawPiece(Piece* piece, int x, int y, int tileSize) {
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
    int boardSize = game.getBoardSize();
    auto board = game.getBoard();
    int tileSize = std::min(width, height) / boardSize;

    for (int i = 0; i < boardSize; ++i) {
        for (int j = 0; j < boardSize; ++j) {
            sf::RectangleShape tile(sf::Vector2f(tileSize, tileSize));
            tile.setPosition(j * tileSize, i * tileSize);

            drawTile(&board[i][j], j * tileSize, i * tileSize, tileSize);

            // Draw a piece if there is one
            auto piece = game.getPieceAt(i, j);
            if (piece != nullptr) {
                drawPiece(piece, j * tileSize, i * tileSize, tileSize);
            }
        }
    }
}
