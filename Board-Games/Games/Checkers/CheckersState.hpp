#ifndef CHECKERS_STATE_HPP
#define CHECKERS_STATE_HPP

#include <Board-Games/BoardGame.hpp>
#include <Board-Games/GameState.hpp>

class CheckersState : public GameState {
  public:
    CheckersState(int boardSize, Player* firstPlayer, Player* secondPlayer);
    void initializeGame() override;
    void promotePiece(int x, int y);

};

#endif