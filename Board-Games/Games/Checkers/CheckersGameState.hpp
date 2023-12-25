#ifndef CHECKERS_GAME_STATE_HPP
#define CHECKERS_GAME_STATE_HPP

#include "../../GameState.hpp"
#include "../../Piece.hpp"
#include <vector>

class CheckersGameState : public GameState {
private:
    bool isMultiCaptureInProgress;
    Piece* capturingPiece;
    std::vector<std::pair<int, int>> availableCaptures;
    

public:
    //constructors
    CheckersGameState();


    // methods
    void initializeGame() override;


};

#endif // CHECKERS_GAME_STATE_HPP