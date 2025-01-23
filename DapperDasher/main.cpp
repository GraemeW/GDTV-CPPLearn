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
    int dasherXFrameCount = 6;
    int dasherYFrameCount = 1;
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
    InitWindow(gameWidth, gameHeight, gameTitle.c_str());
    SetTargetFPS(targetFPS);

    // Character Properties
    Dasher* dasher = new Dasher(dasherTexturePath, dasherXFrameCount, dasherYFrameCount, gameWidth, gameHeight, animationRate);
    dasher->SetDasherProperties(jumpForce, characterMass, jumpBufferTime);

    // Nebula Properties
    NebulaManager* nebulaManager = new NebulaManager(gameWidth, gameHeight, animationRate);
    nebulaManager->SetNebulaManagerProperties(maxNebulaCount, nebulaSpawnPeriod, nebulaSpawnPeriodLimiter, nebulaSpeed);

    // Main Game Loop
    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        // State Updates
        dasher->SetDasherState();
        nebulaManager->SpawnNebulas(dt);

        // Physics Updates
        dasher->IncrementYVelocity(gravityAcceleration, dt);
        dasher->IncrementJumpTimer(dt);
        if (IsKeyDown(KEY_SPACE)) {
            dasher->ApplyJumpForce(dt);
        }
        dasher->ClampVelocity();
        dasher->UpdatePosition(dt);
        nebulaManager->UpdateNebulaPositions(dt);

        // Rendering
        BeginDrawing();
        ClearBackground(backgroundColor);

        dasher->UpdateAnimationFrame(dt);
        dasher->DrawEntity();
        nebulaManager->AnimateAndDrawNebulas(dt);

        EndDrawing();
        // Rendering Ends
    }

    delete dasher;
    delete nebulaManager;
    CloseWindow();
    return 0;
}
