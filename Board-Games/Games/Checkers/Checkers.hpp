#ifndef CHECKERS_HPP
#define CHECKERS_HPP

#include <Board-Games/BoardGame.hpp>
#include <Board-Games/Piece.hpp>
#include <utility>
#include <vector>

class Checkers : public BoardGame {
  public:
    Checkers();
    void initializeGame();
    void loadTextures();
};

#endif