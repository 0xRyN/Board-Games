#ifndef PIECE_HPP
#define PIECE_HPP

#include <Board-Games/GameState.hpp>
#include <Board-Games/common.hpp>
#include <string>
#include <vector>

class GameState;

class Piece {
  protected:
    int x, y;                // Position of the piece on the board
    Color color;             // Color of the piece
    std::string texturePath; // Path to the texture of the piece

  public:
    // Constructor
    Piece(int posX, int posY, Color pieceColor);
    // Virtual destructor
    virtual ~Piece() = default;

    // Getter for the position
    int getX() const;
    int getY() const;

    // Setter for the position
    void setPosition(int posX, int posY);

    // Getter for the color
    Color getColor() const;

    // Getter for the texture path
    std::string getTexturePath() const;

    // Check if a move (capture or not) is valid
    bool isValidMove(GameState& state, int toX, int toY) const;

    // Virtual method for the piece movements. Override these.

    // canMove is for non-capturing moves
    virtual bool canMove(GameState& state, int toX, int toY) const = 0;

    // canCapture is for capturing moves
    virtual bool canCapture(GameState& state, int toX, int toY) const = 0;

    // See all the valid moves for a piece
    virtual const std::vector<Move>*
    getAllAvailableMoves(GameState& state) const = 0;
};

#endif // PIECE_HPP
