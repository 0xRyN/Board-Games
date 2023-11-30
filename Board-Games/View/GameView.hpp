#ifndef GAMEVIEW_HPP
#define GAMEVIEW_HPP

#include <Board-Games/Games/Checkers/Checkers.hpp>
#include <SFML/Graphics.hpp>

class GameView {
  private:
    Checkers& game; // Référence au jeu de plateau
    sf::RenderWindow window;
    void drawTile(Tile* tile, int x, int y, int tileSize);
    void drawPiece(Piece* piece, int x, int y, int tileSize);

  public:
    GameView(Checkers& game, int width = 800, int height = 800);
    void run();       // Lance la boucle de rendu
    void drawBoard(); // Dessine le damier
    // Autres méthodes pour la gestion des interactions et l'affichage des
    void handleClick();
    // pièces
};

#endif
