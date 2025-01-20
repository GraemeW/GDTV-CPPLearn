#include "main.h"

int main(int argc, char const *argv[])
{
    // Volatile World Parameters
    float animationRate{12.0}; // fps
    float gravityAcceleration{9.8};

    // Volatile Character Parameters
    float jumpForce{15.0};
    float jumpBufferTime{0.15};
    float characterMass{1.0};

    // Derived Settings
    float animationFramePeriod = 1 / animationRate;

    // State
    float runningTime{0};
    float yVelocity{0};
    float jumpTimer{999.0};
    bool isInAir(false);

    // Initialization
    InitWindow(gameWidth, gameHeight, gameTitle.c_str());
    SetTargetFPS(targetFPS);

    // Character Properties
    // Note:  Texture loading must be done AFTER window initialization in RayLib
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    Rectangle scarfyRec;
    scarfyRec.width = scarfy.width/6;
    scarfyRec.height = scarfy.height;
    scarfyRec.x = 0;
    scarfyRec.y = 0;
    Vector2 scarfyPosition;
    scarfyPosition.x = gameWidth/2 - scarfyRec.width/2;
    scarfyPosition.y = gameHeight - scarfyRec.height;
    int animationFrame{0};

    // Main Game Loop
    while (!WindowShouldClose()) {
        // State Updates
        isInAir = !(scarfyPosition.y == (gameHeight - scarfy.height));

        // Physics Updates
        yVelocity += gravityAcceleration * GetScaledFrameTime();
        if (IsKeyDown(KEY_SPACE) && !isInAir) {
            yVelocity = -(jumpForce / characterMass) * GetScaledFrameTime();
            jumpTimer = 0;
        }
        if (jumpTimer < jumpBufferTime && IsKeyDown(KEY_SPACE)) { yVelocity -= (jumpForce / characterMass) * GetScaledFrameTime(); }

        jumpTimer += GetFrameTime();
        ClampYVelocity(yVelocity, scarfyPosition.y, gameHeight, scarfy.height);

        // Update Position
        scarfyPosition.y += yVelocity * GetScaledFrameTime();
        scarfyPosition.y = ClampYPosition(scarfyPosition.y, gameHeight, scarfy.height);

        // Rendering
        BeginDrawing();
        ClearBackground(backgroundColor);

        // Update Animation Frame
        runningTime += GetFrameTime();
        if (runningTime >= animationFramePeriod) {
            animationFrame++;
            if (animationFrame > 5) {animationFrame = 0; } // End of animation queue

            if (isInAir) { animationFrame = 3; } // Hold jump animation

            scarfyRec.x = animationFrame * scarfy.width / 6;
            runningTime = 0.0;
        }

        // Drawing
        DrawTextureRec(scarfy, scarfyRec, scarfyPosition, WHITE);
        EndDrawing();
        // Rendering Ends
    }

    UnloadTexture(scarfy);
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
