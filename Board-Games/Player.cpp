#include "Player.hpp"

Player::Player(std::string name, sf::Color color) : name(name), color(color) {}

std::string Player::getName() const {
    return name;
}

sf::Color Player::getColor() const {
    return color;
}
