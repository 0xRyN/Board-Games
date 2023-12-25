#ifndef GAMEVIEW_HPP
#define GAMEVIEW_HPP

#include <SFML/Graphics.hpp>
#include <Board-Games/BoardGame.hpp>

class GameView {
  private:
    BoardGame& game; // Référence au jeu de plateau
    sf::RenderWindow window;
    void drawTile(Tile* tile, int x, int y, int tileSize);
    void drawPiece(Piece* piece, int x, int y, int tileSize);

  public:
    GameView(BoardGame& game, int width = 800, int height = 800);
    void run();       // Lance la boucle de rendu
    void drawBoard(); // Dessine le damier
    // Autres méthodes pour la gestion des interactions et l'affichage des
    //void handleClick() ;
    // pièces
};

#endif
