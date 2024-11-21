#include "Game.h"
#include "raylib.h"
#include "Player.h"

Game::Game() : whitePlayer("WHITE"), blackPlayer("BLACK"), currentPlayer(&whitePlayer), pieceSelected(false), selectedX(-1), selectedY(-1)
{
    // Initialize the board
    board.init();
}

void Game::run()
{
    // Initialize the window
    InitWindow(800, 800, "Chess Game");

    // Main game loop
    while (!WindowShouldClose())
    {
        // Update game state
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            // Handle mouse click for moving pieces
            Vector2 mousePosition = GetMousePosition();
            int xClick = mousePosition.x / 100;
            int yClick = mousePosition.y / 100;

            if (!pieceSelected)
            {
                // Select a piece
                if (board.getPiece(xClick, yClick) != nullptr && board.getPiece(xClick, yClick)->getColor() == currentPlayer->getColor())
                {
                    pieceSelected = true;
                    selectedX = xClick;
                    selectedY = yClick;
                }
            }
            else
            {
                // Move the selected piece
                board.movePiece(selectedX, selectedY, xClick, yClick);
                pieceSelected = false;
                switchTurn();
            }
        }

        // Draw everything
        BeginDrawing();
        ClearBackground(RAYWHITE);

        draw();

        EndDrawing();
    }

    // Close the window
    CloseWindow();
}

void Game::switchTurn()
{
    currentPlayer = (currentPlayer == &whitePlayer) ? &blackPlayer : &whitePlayer;
}

void Game::draw() const
{
    // Draw the UI stuff...
    board.draw();
}

bool Game::isGameOver() const
{
    // Add logic to check if the game is over
    return false;
}