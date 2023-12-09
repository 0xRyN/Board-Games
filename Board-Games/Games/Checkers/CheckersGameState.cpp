#include "CheckersGameState.hpp"

CheckersGameState::CheckersGameState(): isMultiCaptureInProgress(false), capturingPiece(nullptr) {
}

void CheckersGameState::startMultiCapture(Piece* piece) {
    isMultiCaptureInProgress = true;
    capturingPiece = piece;
    availableCaptures.clear();
}

void CheckersGameState::endMultiCapture() {
    isMultiCaptureInProgress = false;
    capturingPiece = nullptr;
    availableCaptures.clear();
}

bool CheckersGameState::multiCaptureInProgress() const {
    return isMultiCaptureInProgress;
}

Piece* CheckersGameState::getCapturingPiece() const {
    return capturingPiece;
}

void CheckersGameState::setAvailableCaptures(const std::vector<std::pair<int, int>>& captures) {
    availableCaptures = captures;
}

const std::vector<std::pair<int, int>>& CheckersGameState::getAvailableCaptures() const {
    return availableCaptures;
}