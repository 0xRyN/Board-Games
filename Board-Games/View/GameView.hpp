#ifndef GAMEVIEW_HPP
#define GAMEVIEW_HPP

#include <Board-Games/BoardGame.hpp>
#include <SFML/Graphics.hpp>

class GameView {
  private:
    BoardGame& game; // Référence au jeu de plateau
    GameState* state;
    sf::RenderWindow window;

    const Tile* selectedTile;
    void selectTile(int x, int y);
    void drawTile(const Tile& tile, int x, int y, int tileSize);
    void drawPiece(const Piece* piece, int x, int y, int tileSize);

  public:
    GameView(BoardGame& game, int width = 800, int height = 800);
    void run();       // Lance la boucle de rendu
    void drawBoard(); // Dessine le damier
    // Autres méthodes pour la gestion des interactions et l'affichage des
    void handleClick();
    // pièces
};

#endif
