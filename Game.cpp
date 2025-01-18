#include "Game.h"
#include "raylib.h"
#include "Player.h"

Game::Game() : whitePlayer("WHITE"), blackPlayer("BLACK"), currentPlayer(&whitePlayer), pieceSelected(false), selectedX(-1), selectedY(-1), gameOver(false)
{
    // Initialize the board
    board.init();
}

Game::~Game()
{
}

void Game::run()
{
    // Initialize the window
    InitWindow(800, 800, "Chess Game");
    whiteKing = LoadTexture("assets/white_king.png");
    whiteQueen = LoadTexture("assets/white_queen.png");
    whiteRook = LoadTexture("assets/white_rook.png");
    whiteBishop = LoadTexture("assets/white_bishop.png");
    whiteKnight = LoadTexture("assets/white_knight.png");
    whitePawn = LoadTexture("assets/white_pawn.png");

    blackKing = LoadTexture("assets/black_king.png");
    blackQueen = LoadTexture("assets/black_queen.png");
    blackRook = LoadTexture("assets/black_rook.png");
    blackBishop = LoadTexture("assets/black_bishop.png");
    blackKnight = LoadTexture("assets/black_knight.png");
    blackPawn = LoadTexture("assets/black_pawn.png");

    // Main game loop
    while (!WindowShouldClose())
    {
        // Update game state
        if (!gameOver)
        {
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
                        validMoves = board.getValidMoves(selectedX, selectedY);
                    }
                }
                else
                {
                    // Move the selected piece
                    if (board.isValidMove(selectedX, selectedY, xClick, yClick))
                    {
                        board.movePiece(selectedX, selectedY, xClick, yClick);

                        board.draw(whiteKing, whiteQueen, whiteRook, whiteBishop, whiteKnight, whitePawn,
                                   blackKing, blackQueen, blackRook, blackBishop, blackKnight, blackPawn);

                        pieceSelected = false;
                        validMoves.clear();

                        switchTurn();
                    }
                    else
                    {
                        pieceSelected = false;
                        validMoves.clear();
                    }
                }
            }

            // Check if the game is over
            if (isGameOver())
            {
                gameOver = true;
            }
        }
        else
        {
            // Check if the player wants to restart the game
            if (IsKeyPressed(KEY_R))
            {
                resetGame();
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
    board.draw(whiteKing, whiteQueen, whiteRook, whiteBishop, whiteKnight, whitePawn,
               blackKing, blackQueen, blackRook, blackBishop, blackKnight, blackPawn);

    int cellSize = 100;

    // Tô xanh lam ô được chọn
    if (pieceSelected)
    {
        DrawRectangle(selectedX * cellSize, selectedY * cellSize, cellSize, cellSize, Fade(BLUE, 0.5f));
    }

    // Tô xanh các ô có thể di chuyển tới
    for (const auto &move : validMoves)
    {
        int x = move.first;
        int y = move.second;
        DrawRectangle(x * cellSize, y * cellSize, cellSize, cellSize, Fade(GREEN, 0.5f));
    }

    // Hiển thị thông báo "Game Over" nếu trò chơi kết thúc
    if (gameOver)
    {
        DrawText("Game Over! Press R to Restart", 200, 400, 20, RED);
    }
}

bool Game::isGameOver() const
{
    // Check if either king is missing
    bool whiteKingAlive = false;
    bool blackKingAlive = false;

    for (int x = 0; x < 8; x++)
    {
        for (int y = 0; y < 8; y++)
        {
            Piece *piece = board.getPiece(x, y);
            if (piece != nullptr)
            {
                if (piece->getType() == "KING")
                {
                    if (piece->getColor() == "WHITE")
                    {
                        whiteKingAlive = true;
                    }
                    else if (piece->getColor() == "BLACK")
                    {
                        blackKingAlive = true;
                    }
                }
            }
        }
    }

    return !(whiteKingAlive && blackKingAlive);
}

void Game::resetGame()
{
    board.init();
    currentPlayer = &whitePlayer;
    pieceSelected = false;
    selectedX = -1;
    selectedY = -1;
    validMoves.clear();
    gameOver = false;
}