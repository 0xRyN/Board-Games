#ifndef PIECE_HPP
#define PIECE_HPP

#include <string>

enum class Color { White, Black };

class Piece {
  protected:
    int x, y;    // Position of the piece on the board
    Color color; // Color of the piece

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

    // Virtual method for the piece movements (to be overridden in derived
    // classes)
    virtual bool canMove(int toX, int toY) const = 0;
    virtual bool canCapture(int fromX, int fromY, int toX, int toY) const = 0;
};

#endif // PIECE_HPP
