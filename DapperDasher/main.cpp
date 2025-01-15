#include "main.h"

int main(int argc, char const *argv[])
{
    // Game Parameters
    float gravity{50000.0};
    float moveSpeed{500.0};
    float jumpForce{150000.0};

    // State
    float yVelocity{0};
    int posY{gameHeight - characterHeight};

    // Initialization
    InitWindow(gameWidth, gameHeight, gameTitle.c_str());
    SetTargetFPS(targetFPS);

    // Main Game Loop
    while (!WindowShouldClose())
    {
        // State Updates
        yVelocity = gravity * GetFrameTime();
        if (IsKeyDown(KEY_SPACE))
        {
            yVelocity -= jumpForce * GetFrameTime();
        }

        // Update Position
        posY += yVelocity * GetFrameTime();
        posY = ClampYPosition(posY, gameHeight, characterHeight);

        // Rendering
        BeginDrawing();
        ClearBackground(backgroundColor);

        DrawRectangle(gameWidth/2, posY, characterWidth, characterHeight, BLUE);

        EndDrawing();
        // Rendering Ends
    }

    CloseWindow();
    return 0;
}

int ClampYPosition(int yPos, int gameHeight, int characterHeight)
{
    if (yPos > (gameHeight - characterHeight)) { yPos = gameHeight - characterHeight; }
    if (yPos < 0) { yPos = 0; }

    return yPos;
}
