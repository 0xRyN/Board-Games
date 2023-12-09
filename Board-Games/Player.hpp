#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "common.hpp"
#include <string>

class Player {
  public:
    Player(const std::string& name, const Color& color);

    std::string getName() const;
    Color getColor() const;

  private:
    std::string name;
    Color color;
};

#endif // PLAYER_HPP