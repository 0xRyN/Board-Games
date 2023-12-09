#include "CheckersRules.hpp"

bool CheckersRules::isValidMove(const BoardGame& game, int fromX, int fromY,
                                int toX, int toY) const {
    CheckersGameState* state =
        dynamic_cast<CheckersGameState*>(game.getGameState());
    Piece* piece = game.getPieceAt(fromX, fromY);

    // If multi-capture is in progress, check if the move is a valid
    // continuation
    if (state->multiCaptureInProgress()) {
        return (piece == state->getCapturingPiece()) &&
               isValidCaptureMove(piece, toX, toY);
    }

    // Normal move validation
    // ...

    return true;
}

bool CheckersRules::isValidCaptureMove(Piece* piece, int toX, int toY) const {
    

}