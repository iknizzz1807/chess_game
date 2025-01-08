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
    // void draw() const;
    void draw(Texture2D whiteKing, Texture2D whiteQueen, Texture2D whiteRook, Texture2D whiteBishop, Texture2D whiteKnight, Texture2D whitePawn,
              Texture2D blackKing, Texture2D blackQueen, Texture2D blackRook, Texture2D blackBishop, Texture2D blackKnight, Texture2D blackPawn) const;
    Piece *getPiece(int x, int y) const;
    void movePiece(int startX, int startY, int endX, int endY);
    bool isValidMove(int startX, int startY, int endX, int endY) const; // This should be get called from the movePiece function
    bool isCheckMate() const;                                           // Input: the color from the piece you want to check
};

#endif