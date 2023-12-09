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
    CheckersGameState();
    void startMultiCapture(Piece* piece);
    void endMultiCapture();
    bool multiCaptureInProgress() const;
    Piece* getCapturingPiece() const;
    void setAvailableCaptures(const std::vector<std::pair<int, int>>& captures);
    const std::vector<std::pair<int, int>>& getAvailableCaptures() const;
};

#endif // CHECKERS_GAME_STATE_HPP