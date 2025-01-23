#include "main.h"
#include <string>

int main(int argc, char const *argv[])
{
    // Volatile World Parameters
    float animationRate{12.0}; // fps
    float gravityAcceleration{9.8};

    // Volatile Character Parameters
    string dasherTexturePath = "textures/scarfy.png";
    int dasherXFrameCount = 6;
    int dasherYFrameCount = 1;
    float jumpForce{40.0};
    float characterMass{1.0};
    float jumpBufferTime{0.25};

    // Initialization
    InitWindow(gameWidth, gameHeight, gameTitle.c_str());
    SetTargetFPS(targetFPS);

    // Character Properties
    Dasher* dasher = new Dasher(dasherTexturePath, dasherXFrameCount, dasherYFrameCount, gameWidth, gameHeight, animationRate);
    dasher->SetDasherProperties(jumpForce, characterMass, jumpBufferTime);

    // Main Game Loop
    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        // State Updates
        dasher->SetDasherState();

        // Physics Updates
        dasher->IncrementYVelocity(gravityAcceleration, dt);
        dasher->IncrementJumpTimer(dt);
        if (IsKeyDown(KEY_SPACE)) {
            dasher->ApplyJumpForce(dt);
        }
        dasher->ClampVelocity();
        dasher->UpdatePosition(dt);

        // Rendering
        BeginDrawing();
        ClearBackground(backgroundColor);
        dasher->UpdateAnimationFrame(dt);
        dasher->DrawEntity();
        EndDrawing();
        // Rendering Ends
    }

    free(dasher);
    CloseWindow();
    return 0;
}
