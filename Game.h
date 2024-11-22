#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Board.h"

class Game
{
private:
    Player whitePlayer;
    Player blackPlayer;
    Player *currentPlayer;
    Board board;
    bool pieceSelected;
    int selectedX, selectedY;

    Texture2D whiteKing;
    Texture2D whiteQueen;
    Texture2D whiteRook;
    Texture2D whiteBishop;
    Texture2D whiteKnight;
    Texture2D whitePawn;
    Texture2D blackKing;
    Texture2D blackQueen;
    Texture2D blackRook;
    Texture2D blackBishop;
    Texture2D blackKnight;
    Texture2D blackPawn;

public:
    Game();
    ~Game();
    void run();
    void switchTurn();
    void draw() const; // Draw the UI and stuff not draw the chess
    bool isGameOver() const;
    // Const means this is just for running and not change anything
};

#endif // GAME_H