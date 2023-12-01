
#include "Player.hpp"

Player::Player(const std::string& name, const Color& color)
    : name(name), color(color) {
}

std::string Player::getName() const {
    return name;
}

Color Player::getColor() const {
    return color;
}
