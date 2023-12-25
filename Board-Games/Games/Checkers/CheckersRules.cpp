 #include "CheckersRules.hpp"

std::vector<std::pair<int, int>>
CheckersRules::getAvailableActions(const BoardGame& game, int x, int y) {
    std::vector<std::pair<int, int>> actions;
    // Get the color of the piece
    Color color = game.getBoard()[x][y].getPiece()->getColor();

    // Définir des constantes pour les directions
    const int WHITE_DIRECTION = 1;
    const int BLACK_DIRECTION = -1;

    // Utiliser les constantes dans le code
    int direction = (color == Color::White) ? WHITE_DIRECTION : BLACK_DIRECTION;

    // Iterate through all possible moves in the valid direction
    for (int dx = -1; dx <= 1; dx++) {
        int toX = x + dx;
        int toY = y + direction;

        // Check if the move is within the board boundaries
        if (this->isValidMove(game, x, y, toX, toY)) {
            // Check if the move is valid or a capture
            actions.emplace_back(toX, toY);
        }
    }

    return actions;
}

bool CheckersRules::isValidMove(const BoardGame& game, int fromX, int fromY, int toX, int toY) const {
    if (isValidSimpleMove(game, fromX, fromY, toX, toY)) {
        return false;
    }
    if (isValidCaptureMove(game, fromX, fromY, toX, toY)) {
        return false;
    }
    return true;
}

bool CheckersRules::isValidCaptureMove(const BoardGame& game, int fromX,
                                       int fromY, int toX, int toY) const {

    // Check if the move is diagonal and of length 2
    if (!isDiagonalStep(2, fromX, fromY, toX, toY)) {
        return false;
    }

    // check if the piece is of the opposite color
    if (!isCapturablePiece(game, fromX, fromY, toX, toY)) {
        return false;
    }

    // Check if the destination square is empty
    if (!game.isEmpty(toX, toY)) {
        return false;
    }

    return true;
}

std::vector<std::pair<int, int>> CheckersRules::getAvailableCaptureMoves(const BoardGame& game ,int x, int y) {
    std::vector<std::pair<int, int>> captures;
    std::vector<std::pair<int, int>> actions = getAvailableActions(game, x, y);
    for (auto action : actions) {
        int toX = action.first;
        int toY = action.second;
        if (this->isValidCaptureMove(game,x, y, toX, toY)) {
            captures.emplace_back(toX, toY);
        }
    }
    return captures;
}
bool CheckersRules::isValidSimpleMove(const BoardGame& game, int fromX,
                                      int fromY, int toX, int toY) const {
    // check if the move is diagonal
    if (!isDiagonalStep(1, fromX, fromY, toX, toY)) {
        return false;
    }
    // check if the move is forward
    if (!isMoveForward(game, fromX, fromY, toX, toY)) {
        return false;
    }
    // check if the tile is empty
    if (game.getPieceAt(toX, toY) != nullptr) {
        return false;
    }
    return true;
}


bool CheckersRules::isDiagonalStep(int step, int fromX, int fromY, int toX,
                                   int toY) const {
    // check if the move is diagonal and of length 1
    return abs(fromX - toX) == step && abs(fromY - toY) == step;
}

bool CheckersRules::isMoveForward(const BoardGame& game, int fromX, int fromY,
                                  int toX, int toY) const {
    // if the piece is white, it can only move down
    if (game.getPieceAt(fromX, fromY)->getColor() == Color::White) {
        return fromY < toY;
    }
    // if the piece is black, it can only move up
    return fromY > toY;
}

bool CheckersRules::isCapturablePiece(const BoardGame& game, int fromX,
                                      int fromY, int toX, int toY) const {
    // Get the position of the jumped piece
    int midX = (fromX + toX) / 2;
    int midY = (fromY + toY) / 2;
    Piece* jumpedPiece = game.getPieceAt(midX, midY);

    // Check if there is a piece to jump over and it's of the opposite color
    if (jumpedPiece == nullptr) {
        return false;
    }
    Color color = game.getPieceAt(fromX, fromY)->getColor();
    if (jumpedPiece->getColor() == color) {
        return false;
    }
    return true;
}

void CheckersRules::showReachableTiles(BoardGame& game, int x, int y)  {
    std::vector<std::pair<int, int>> actions  = getAvailableActions(game, x, y);
    for (auto action : actions) {
        int toX = action.first;
        int toY = action.second;
        auto board = game.getBoard()[toX][toY];
        board.setReachable(true);
    }
}
 */