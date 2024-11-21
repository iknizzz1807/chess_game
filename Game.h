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

public:
    Game();
    void run();
    void switchTurn();
    void draw() const; // Draw the UI and stuff not draw the chess
    bool isGameOver() const;
    // Const means this is just for running and not change anything
};

#endif // GAME_H