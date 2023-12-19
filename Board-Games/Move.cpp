#include "Move.hpp"

Move::Move(int fromX, int fromY, int toX, int toY, bool isCaptureMove)
    : fromX(fromX), fromY(fromY), toX(toX), toY(toY),
      isCaptureMove(isCaptureMove) {
}

std::ostream& operator<<(std::ostream& os, const Move& move) {
    std::string var = (move.isCaptureMove) ? "Capture " : "Move ";
    os << var << "from (" << move.fromX << ", " << move.fromY << ") to ("
       << move.toX << ", " << move.toY << ")";
    return os;
}
