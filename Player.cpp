#include "Player.h"
#include <string>

Player::Player(std::string color) : color(color) {}

std::string Player::getColor() const
{
    return this->color;
}