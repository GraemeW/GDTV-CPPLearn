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

    // Volatile Background Parameters
    float backgroundForegroundScrollSpeed{500};
    float backgroundBuildingsScrollSpeed{200};
    float backgroundBackingScrollSpeed{50};

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

    // Finish Line
    int finishLine{10}; // Nebulae to pass

    // Background Properties
    Background* backgroundBuildings = new Background(BackgroundType::BUILDINGS, backgroundBuildingsScrollSpeed, gameDimensions);
    Background* backgroundBacking = new Background(BackgroundType::BACKING, backgroundBackingScrollSpeed, gameDimensions);
    Background* backgroundForeground = new Background(BackgroundType::FOREGROUND, backgroundForegroundScrollSpeed, gameDimensions);

    // Main Game Loop
    bool gameFinished = false;
    bool gameResult = false;
    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        dasher->SetDeltaFrameTime(dt);
        nebulaManager->SetDeltaFrameTime(dt);
        backgroundBuildings->SetDeltaFrameTime(dt);
        backgroundBacking->SetDeltaFrameTime(dt);
        backgroundForeground->SetDeltaFrameTime(dt);

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

        backgroundBuildings->AnimateBackground();
        backgroundBacking->AnimateBackground();
        backgroundForeground->AnimateBackground();

        // Rendering
        BeginDrawing();
        ClearBackground(backgroundColor);

        backgroundBacking->DrawBackground();
        backgroundBuildings->DrawBackground();
        backgroundForeground->DrawBackground();

        dasher->UpdateAnimationFrame();
        dasher->DrawEntity();

        // Win
        if (!gameFinished && nebulaManager->GetTotalNebulaCount() >= finishLine) {
            gameFinished = true;
            gameResult = true;
        }
        // Lose
        if (!gameFinished && nebulaManager->CheckNebulaCollisions(dasher->GetPositionalRect())) {
            gameFinished = true;
            gameResult = false;
        }
        // Draw Results
        if (gameFinished) {
            if (gameResult) { DrawText("You Win!", gameDimensions[0]/2 - 100, gameDimensions[1]/2, 48, GREEN); }
            else { DrawText("You Lose!", gameDimensions[0]/2 - 100, gameDimensions[1]/2, 48, RED); }
        }

        // Otherwise draw nebulae
        if (!gameFinished) {
            nebulaManager->AnimateAndDrawNebulas();
        }
        EndDrawing();
        // Rendering Ends
    }

    delete dasher;
    delete nebulaManager;
    CloseWindow();
    return 0;
}
