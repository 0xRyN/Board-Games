#ifndef CHECKERS_HPP
#define CHECKERS_HPP


#include "../../BoardGame.hpp"

class CheckersGame : public BoardGame {
public:
    CheckersGame();
    ~CheckersGame();
    void loadTextures() override;
    void movePiece(int fromX, int fromY, int toX, int toY) override;
    void changePlayer() override;
    bool isEmpty(int x, int y) const override;
};


#endif