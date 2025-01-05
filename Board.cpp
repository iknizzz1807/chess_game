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
        board[x][1] = new Piece("PAWN", "BLACK", x, 1);
        board[x][6] = new Piece("PAWN", "WHITE", x, 6);
    }

    // Place rooks
    board[0][0] = new Piece("ROOK", "BLACK", 0, 0);
    board[7][0] = new Piece("ROOK", "BLACK", 7, 0);
    board[0][7] = new Piece("ROOK", "WHITE", 0, 7);
    board[7][7] = new Piece("ROOK", "WHITE", 7, 7);

    // Place knights
    board[1][0] = new Piece("KNIGHT", "BLACK", 1, 0);
    board[6][0] = new Piece("KNIGHT", "BLACK", 6, 0);
    board[1][7] = new Piece("KNIGHT", "WHITE", 1, 7);
    board[6][7] = new Piece("KNIGHT", "WHITE", 6, 7);

    // Place bishops
    board[2][0] = new Piece("BISHOP", "BLACK", 2, 0);
    board[5][0] = new Piece("BISHOP", "BLACK", 5, 0);
    board[2][7] = new Piece("BISHOP", "WHITE", 2, 7);
    board[5][7] = new Piece("BISHOP", "WHITE", 5, 7);

    // Place queens
    board[3][0] = new Piece("QUEEN", "BLACK", 3, 0);
    board[3][7] = new Piece("QUEEN", "WHITE", 3, 7);

    // Place kings
    board[4][0] = new Piece("KING", "BLACK", 4, 0);
    board[4][7] = new Piece("KING", "WHITE", 4, 7);
}

Piece *Board::getPiece(int x, int y) const
{
    if (x >= 0 && x < 8 && y >= 0 && y < 8)
    {
        return board[x][y];
    }
    return nullptr;
}

void Board::draw(Texture2D whiteKing, Texture2D whiteQueen, Texture2D whiteRook, Texture2D whiteBishop, Texture2D whiteKnight, Texture2D whitePawn,
                 Texture2D blackKing, Texture2D blackQueen, Texture2D blackRook, Texture2D blackBishop, Texture2D blackKnight, Texture2D blackPawn) const
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
                Texture2D texture;
                std::string type = this->board[x][y]->getType();
                std::string color = this->board[x][y]->getColor();

                if (type == "KING")
                    texture = (color == "WHITE") ? whiteKing : blackKing;
                else if (type == "QUEEN")
                    texture = (color == "WHITE") ? whiteQueen : blackQueen;
                else if (type == "ROOK")
                    texture = (color == "WHITE") ? whiteRook : blackRook;
                else if (type == "BISHOP")
                    texture = (color == "WHITE") ? whiteBishop : blackBishop;
                else if (type == "KNIGHT")
                    texture = (color == "WHITE") ? whiteKnight : blackKnight;
                else if (type == "PAWN")
                    texture = (color == "WHITE") ? whitePawn : blackPawn;

                int posX = x * cellSize + (cellSize - texture.width) / 2;
                int posY = y * cellSize + (cellSize - texture.height) / 2;

                DrawTexture(texture, posX, posY, WHITE);
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
    }
}

bool Board::isValidMove(int targetX, int targetY) const
{
    // Add logic to check if the move is valid
    // For simplicity, let's assume all moves are valid
    return true;
}