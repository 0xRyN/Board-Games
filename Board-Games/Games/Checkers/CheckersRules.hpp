#ifndef CHECKERS_RULES_HPP
#define CHECKERS_RULES_HPP 

#include "../../GameRules.hpp"
#include "CheckersGameState.hpp"



class CheckersRules : public GameRules {
public:
    bool isValidMove(const BoardGame& game, int fromX, int fromY, int toX, int toY) const override {
        CheckersGameState* state = dynamic_cast<CheckersGameState*>(game.getGameState());
        Piece* piece = game.getPieceAt(fromX, fromY);

        // If multi-capture is in progress, check if the move is a valid continuation
        if (state->multiCaptureInProgress()) {
            return (piece == state->getCapturingPiece()) && isValidCaptureMove(piece, toX, toY);
        }

        // Normal move validation
        // ...

        return true;
    }

private:
    bool isValidCaptureMove(Piece* piece, int toX, int toY) const {
        // Logic to determine if the move is a valid capture move
        // ...
    }
};


#endif