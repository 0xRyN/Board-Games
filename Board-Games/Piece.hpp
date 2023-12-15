#ifndef PIECE_HPP
#define PIECE_HPP

#include "common.hpp"
#include <string>

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

};
#endif // PIECE_HPP
