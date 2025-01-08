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
    if (isValidMove(startX, startY, endX, endY))
    {
        delete board[endX][endY];                   // Remove the piece at the destination
        board[endX][endY] = board[startX][startY];  // Move the choosen piece to the destination (just change the pointer, this pointer still has the startX startY position attribute though)
        board[startX][startY] = nullptr;            // Free the slot of the choosen piece
        board[endX][endY]->setPosition(endX, endY); // Actually update the position instead of just update the pointers like above
    }
}

bool Board::isValidMove(int startX, int startY, int endX, int endY) const
{
    // Current Bug: when try to move queen or king it stops the game
    // Check if the move is within the bounds of the board
    if (startX < 0 || startX >= 8 || startY < 0 || startY >= 8 || endX < 0 || endX >= 8 || endY < 0 || endY >= 8)
    {
        return false;
    }

    // Check if there is a piece at the starting position
    Piece *piece = board[startX][startY];
    if (piece == nullptr)
    {
        return false;
    }

    // Check if the destination is the same as the starting position
    if (startX == endX && startY == endY)
    {
        return false;
    }

    // Check if the destination has a piece of the same color
    Piece *destinationPiece = board[endX][endY];
    if (destinationPiece != nullptr && destinationPiece->getColor() == piece->getColor())
    {
        return false;
    }

    // Add specific rules for each type of piece
    std::string type = piece->getType();
    if (type == "PAWN")
    {
        // Add logic for pawn movement
        int direction = (piece->getColor() == "WHITE") ? -1 : 1;
        if (startX == endX && board[endX][endY] == nullptr)
        {
            // Move forward
            if (endY == startY + direction)
            {
                return true;
            }
            // Move two squares forward from the starting position
            if ((startY == 1 && piece->getColor() == "BLACK" || startY == 6 && piece->getColor() == "WHITE") && endY == startY + 2 * direction && board[endX][startY + direction] == nullptr)
            {
                return true;
            }
        }
        else if (abs(startX - endX) == 1 && endY == startY + direction && board[endX][endY] != nullptr)
        {
            // Capture diagonally
            return true;
        }
    }
    else if (type == "ROOK")
    {
        // Add logic for rook movement
        if (startX == endX || startY == endY)
        {
            // Check if the path is clear
            int xDirection = (endX - startX) == 0 ? 0 : (endX - startX) / abs(endX - startX);
            int yDirection = (endY - startY) == 0 ? 0 : (endY - startY) / abs(endY - startY);
            int x = startX + xDirection;
            int y = startY + yDirection;
            while (x != endX || y != endY)
            {
                if (board[x][y] != nullptr)
                {
                    return false;
                }
                x += xDirection;
                y += yDirection;
            }
            return true;
        }
    }
    else if (type == "KNIGHT")
    {
        // Add logic for knight movement
        if ((abs(startX - endX) == 2 && abs(startY - endY) == 1) || (abs(startX - endX) == 1 && abs(startY - endY) == 2))
        {
            return true;
        }
    }
    else if (type == "BISHOP")
    {
        // Add logic for bishop movement
        if (abs(startX - endX) == abs(startY - endY))
        {
            // Check if the path is clear
            int xDirection = (endX - startX) / abs(endX - startX);
            int yDirection = (endY - startY) / abs(endY - startY);
            int x = startX + xDirection;
            int y = startY + yDirection;
            while (x != endX || y != endY)
            {
                if (board[x][y] != nullptr)
                {
                    return false;
                }
                x += xDirection;
                y += yDirection;
            }
            return true;
        }
    }
    else if (type == "QUEEN")
    {
        // Add logic for queen movement
        if (startX == endX || startY == endY || abs(startX - endX) == abs(startY - endY))
        {
            // Check if the path is clear
            int xDirection = (endX - startX) == 0 ? 0 : (endX - startX) / abs(endX - startX);
            int yDirection = (endY - startY) == 0 ? 0 : (endY - startY) / abs(endY - startY);
            int x = startX + xDirection;
            int y = startY + yDirection;
            while (x != endX || y != endY)
            {
                if (board[x][y] != nullptr)
                {
                    return false;
                }
                x += xDirection;
                y += yDirection;
            }
            return true;
        }
    }
    else if (type == "KING")
    {
        // Add logic for king movement
        if (abs(startX - endX) <= 1 && abs(startY - endY) <= 1)
        {
            return true;
        }
    }

    // If none of the conditions are met, the move is not valid
    return false;
}