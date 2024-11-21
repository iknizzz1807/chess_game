#ifndef PLAYER_H
#define PLAYER_H

#include "Board.h"
#include <string>

class Player
{
private:
    std::string color;

public:
    Player(std::string color);
    std::string getColor() const;
    bool makeMove(Board &board, int startX, int startY, int endX, int endY);
};

#endif // PLAYER_H