#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <Board-Games/common.hpp>
#include <iostream>
#include <string>

class Player {
  private:
    std::string name;
    Color color;

  public:
    Player(const std::string& name, const Color& color);

    std::string getName() const;
    Color getColor() const;

    friend std::ostream& operator<<(std::ostream& os, const Player& player);
};

#endif // PLAYER_HPP