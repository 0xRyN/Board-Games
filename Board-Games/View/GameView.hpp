#ifndef GAMEVIEW_HPP
#define GAMEVIEW_HPP

#include <Board-Games/BoardGame.hpp>
#include <SFML/Graphics.hpp>

class GameView {
  private:
    BoardGame& game; // Référence au jeu de plateau
    sf::RenderWindow window;

  public:
    GameView(BoardGame& game, int width = 800, int height = 800);
    void run();       // Lance la boucle de rendu
    void drawBoard(); // Dessine le damier
    // Autres méthodes pour la gestion des interactions et l'affichage des
    // pièces
};

#endif
