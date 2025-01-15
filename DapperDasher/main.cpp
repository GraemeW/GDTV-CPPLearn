#include "main.h"

int main(int argc, char const *argv[])
{
    // World Parameters
    float gravityAcceleration{9.8};

    // Character Parameters
    float jumpForce{15.0};
    float jumpBufferTime{0.15};
    float characterMass{1.0};
    float moveSpeed{5.0};

    // State
    float yVelocity{0};
    float jumpTimer{999.0};
    int yPosition{gameHeight - characterHeight};

    // Initialization
    InitWindow(gameWidth, gameHeight, gameTitle.c_str());
    SetTargetFPS(targetFPS);

    // Main Game Loop
    while (!WindowShouldClose())
    {
        // Physics Updates
        yVelocity += gravityAcceleration * GetScaledFrameTime();
        if (IsKeyDown(KEY_SPACE) && yPosition == (gameHeight - characterHeight))
        {
            yVelocity = -(jumpForce / characterMass) * GetScaledFrameTime();
            jumpTimer = 0;
        }
        if (jumpTimer < jumpBufferTime && IsKeyDown(KEY_SPACE)) { yVelocity -= (jumpForce / characterMass) * GetScaledFrameTime(); }

        jumpTimer += GetFrameTime();
        ClampYVelocity(yVelocity, yPosition, gameHeight, characterHeight);

        // Update Position
        yPosition += yVelocity * GetScaledFrameTime();
        yPosition = ClampYPosition(yPosition, gameHeight, characterHeight);

        // Rendering
        BeginDrawing();
        ClearBackground(backgroundColor);

        DrawRectangle(gameWidth/2, yPosition, characterWidth, characterHeight, BLUE);

        EndDrawing();
        // Rendering Ends
    }

    CloseWindow();
    return 0;
}

float GetScaledFrameTime()
{
    return (GetFrameTime() * 50.0); // Fixed
}

float ClampYVelocity(float yVelocity, int yPos, int gameHeight, int characterHeight)
{
    if (yPos >= (gameHeight - characterHeight) && yVelocity > 0) { yVelocity = 0; }
    return yVelocity;
}

int ClampYPosition(int yPos, int gameHeight, int characterHeight)
{
    if (yPos > (gameHeight - characterHeight)) { yPos = gameHeight - characterHeight; }
    if (yPos < 0) { yPos = 0; }

    return yPos;
}
