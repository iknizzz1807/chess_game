#ifndef BOARD_H
#define BOARD_H

#include "raylib.h"
#include "Piece.h"

class Board
{
private:
    Piece *board[8][8];

public:
    Board();

    void init();
    void draw() const;
    Piece *getPiece(int x, int y) const;
    void movePiece(int startX, int startY, int endX, int endY);
    bool isValidMove(int targetX, int targetY) const; // This should be get called from the movePiece function
    bool isCheckMate() const;                         // Input: the color from the piece you want to check
};

#endif