#include "Piece.h"

Piece::Piece(std::string type, std::string color, int x, int y)
    : type(type), color(color), x(x), y(y) {}

std::string Piece::getType() const
{
    return type;
}

std::string Piece::getColor() const
{
    return color;
}

std::pair<int, int> Piece::getPosition() const
{
    return std::make_pair(x, y);
}

void Piece::setPosition(int newX, int newY)
{
    x = newX;
    y = newY;
}