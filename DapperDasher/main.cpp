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

    // Volatile Hazard Parameters
    string nebulaTexturePath = "textures/12_nebula_spritesheet.png";
    int nebulaXFrameCount{8};
    int nebulaYFrameCount{8};
    float nebulaSpeed{-5.0};

    // Initialization
    InitWindow(gameWidth, gameHeight, gameTitle.c_str());
    SetTargetFPS(targetFPS);

    // Character Properties
    Dasher* dasher = new Dasher(dasherTexturePath, dasherXFrameCount, dasherYFrameCount, gameWidth, gameHeight, animationRate);
    dasher->SetDasherProperties(jumpForce, characterMass, jumpBufferTime);

    // Nebula Properties
    Nebula* nebula = new Nebula(nebulaTexturePath, nebulaXFrameCount, nebulaYFrameCount, gameWidth, gameHeight, animationRate);
    nebula->OverridePosition(gameWidth, gameHeight - nebula->entityHeight);
    nebula->SetNebulaSpeed(nebulaSpeed);

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
        nebula->UpdatePosition(dt);

        // Rendering
        BeginDrawing();
        ClearBackground(backgroundColor);
        // Dasher
        dasher->UpdateAnimationFrame(dt);
        dasher->DrawEntity();

        // Nebula
        nebula->UpdateAnimationFrame(dt);
        nebula->DrawEntity();

        EndDrawing();
        // Rendering Ends
    }

    delete dasher;
    delete nebula;
    CloseWindow();
    return 0;
}
