#ifndef MOVE_CPP
#define MOVE_CPP

#include <iostream>

class Move {
  public:
    int fromX, fromY, toX, toY;
    bool isCaptureMove;

    Move(int fromX, int fromY, int toX, int toY, bool isCaptureMove);
    friend std::ostream& operator<<(std::ostream& os, const Move& move);
    friend bool operator==(const Move& lhs, const Move& rhs);
};

#endif