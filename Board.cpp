#include "Board.h"
#include <string>

Board::Board()
{
    // Initialize all squares to nullptr
    for (int x = 0; x < 8; x++)
    {
        for (int y = 0; y < 8; y++)
        {
            board[x][y] = nullptr;
        }
    }
}

void Board::init()
{
    // Place pawns
    for (int x = 0; x < 8; x++)
    {
        board[x][1] = new Piece("PAWN", "WHITE", x, 1);
        board[x][6] = new Piece("PAWN", "BLACK", x, 6);
    }

    // Place rooks
    board[0][0] = new Piece("ROOK", "WHITE", 0, 0);
    board[7][0] = new Piece("ROOK", "WHITE", 7, 0);
    board[0][7] = new Piece("ROOK", "BLACK", 0, 7);
    board[7][7] = new Piece("ROOK", "BLACK", 7, 7);

    // Place knights
    board[1][0] = new Piece("KNIGHT", "WHITE", 1, 0);
    board[6][0] = new Piece("KNIGHT", "WHITE", 6, 0);
    board[1][7] = new Piece("KNIGHT", "BLACK", 1, 7);
    board[6][7] = new Piece("KNIGHT", "BLACK", 6, 7);

    // Place bishops
    board[2][0] = new Piece("BISHOP", "WHITE", 2, 0);
    board[5][0] = new Piece("BISHOP", "WHITE", 5, 0);
    board[2][7] = new Piece("BISHOP", "BLACK", 2, 7);
    board[5][7] = new Piece("BISHOP", "BLACK", 5, 7);

    // Place queens
    board[3][0] = new Piece("QUEEN", "WHITE", 3, 0);
    board[3][7] = new Piece("QUEEN", "BLACK", 3, 7);

    // Place kings
    board[4][0] = new Piece("KING", "WHITE", 4, 0);
    board[4][7] = new Piece("KING", "BLACK", 4, 7);
}

Piece *Board::getPiece(int x, int y) const
{
    if (x >= 0 && x < 8 && y >= 0 && y < 8)
    {
        return board[x][y];
    }
    return nullptr;
}

void Board::draw() const
{
    int cellSize = 100;
    for (int x = 0; x < 8; x++)
    {
        for (int y = 0; y < 8; y++)
        {
            Color cellColor = (x + y) % 2 == 0 ? LIGHTGRAY : DARKGRAY;
            DrawRectangle(x * cellSize, y * cellSize, cellSize, cellSize, cellColor);

            // Draw the chess if there is available
            if (this->board[x][y] != nullptr)
            {
                char pieceChar;
                std::string type = this->board[x][y]->getType();
                if (type == "KING")
                    pieceChar = 'K';
                else if (type == "QUEEN")
                    pieceChar = 'Q';
                else if (type == "ROOK")
                    pieceChar = 'R';
                else if (type == "BISHOP")
                    pieceChar = 'B';
                else if (type == "KNIGHT")
                    pieceChar = 'N';
                else if (type == "PAWN")
                    pieceChar = 'P';
                else
                    pieceChar = ' ';

                std::string pieceStr(1, pieceChar); // Because the DrawText function needs this
                DrawText(pieceStr.c_str(), x * cellSize + 40, y * cellSize + 40, 40, this->board[x][y]->getColor() == "WHITE" ? WHITE : BLACK);
            }
        }
    }
}

void Board::movePiece(int startX, int startY, int endX, int endY)
{
    if (isValidMove(endX, endY))
    {
        delete board[endX][endY];                   // Remove the piece at the destination
        board[endX][endY] = board[startX][startY];  // Move the choosen piece to the destination (just change the pointer, this pointer still has the startX startY position attribute though)
        board[startX][startY] = nullptr;            // Free the slot of the choosen piece
        board[endX][endY]->setPosition(endX, endY); // Actually update the position instead of just update the pointers like above
        draw();
    }
}

bool Board::isValidMove(int targetX, int targetY) const
{
    // Add logic to check if the move is valid
    // For simplicity, let's assume all moves are valid
    return true;
}