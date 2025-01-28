#include "main.h"
#include <string>
#include <vector>

int main(int argc, char const *argv[])
{
    /* TUNABLES */
    // Volatile World Parameters
    float animationRate{12.0}; // fps
    float gravityAcceleration{9.8};

    // Volatile Character Parameters
    string dasherTexturePath = "textures/scarfy.png";
    int dasherxyFrameCount[2] = {6, 1};
    float jumpForce{80.0};
    float characterMass{0.65};
    float jumpBufferTime{0.25};

    // Volatile Hazard Parameters
    int maxNebulaCount{8};
    Vector2 nebulaSpawnPeriod{0.2, 1.5};
    float nebulaSpawnPeriodLimiter{0.5};
    float nebulaSpeed{-25.0};

    /* GAME CODE */
    // Initialization
    InitWindow(gameDimensions[0], gameDimensions[1], gameTitle.c_str());
    SetTargetFPS(targetFPS);

    // Character Properties
    Dasher* dasher = new Dasher(dasherTexturePath, dasherxyFrameCount, gameDimensions, animationRate);
    dasher->SetDasherProperties(jumpForce, characterMass, jumpBufferTime);

    // Nebula Properties
    NebulaManager* nebulaManager = new NebulaManager(gameDimensions, animationRate);
    nebulaManager->SetNebulaManagerProperties(maxNebulaCount, nebulaSpawnPeriod, nebulaSpawnPeriodLimiter, nebulaSpeed);

    // Main Game Loop
    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        dasher->SetDeltaFrameTime(dt);
        nebulaManager->SetDeltaFrameTime(dt);

        // State Updates
        dasher->SetDasherState();
        nebulaManager->SpawnNebulas();

        // Physics Updates
        dasher->IncrementYVelocity(gravityAcceleration);
        dasher->IncrementJumpTimer();
        if (IsKeyDown(KEY_SPACE)) {
            dasher->ApplyJumpForce();
        }
        dasher->ClampVelocity();
        dasher->UpdatePosition();
        nebulaManager->UpdateNebulaPositions();

        // Rendering
        BeginDrawing();
        ClearBackground(backgroundColor);

        dasher->UpdateAnimationFrame();
        dasher->DrawEntity();
        nebulaManager->AnimateAndDrawNebulas();

        EndDrawing();
        // Rendering Ends
    }

    delete dasher;
    delete nebulaManager;
    CloseWindow();
    return 0;
}
