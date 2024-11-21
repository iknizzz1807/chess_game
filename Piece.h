#ifndef PIECE_H
#define PIECE_H

#include <utility>
#include <string>

// This class presents each square on the field
class Piece
{
private:
    std::string type;
    std::string color;
    int x, y; // The position on the board

public:
    Piece(std::string type, std::string color, int x, int y);

    void setPosition(int newX, int newY); // This is waitng to be called from the movePiece function from class Board
                                          // Because the move piece action contains: move the pointer to the destination and change the x, y value of that pointer
    std::string getType() const;
    std::string getColor() const;
    std::pair<int, int> getPosition() const;
};

#endif