#ifndef CHECKERS_HPP
#define CHECKERS_HPP

#include "../../BoardGame.hpp"

class CheckersGame : public BoardGame {
  public:
    CheckersGame();
    ~CheckersGame() = default;

    void loadTextures() override;
   
};

#endif
