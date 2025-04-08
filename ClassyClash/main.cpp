#include "main.h"
#include <string>
#include <vector>

int main(int argc, char const *argv[])
{
    /* GAME CODE */
    // Initialization
    InitWindow(gameDimensions.x, gameDimensions.y, gameTitle.c_str());
    SetTargetFPS(targetFPS);
    WorldMap* worldMap = new WorldMap(gameDimensions);
    PropManager* propManager = new PropManager(gameDimensions);
    Player* player = new Player(knightTexturePathActive, knightTexturePathIdle, knightxyFrameCount, knightPadding, gameDimensions, animationRate);
    player->OverridePosition(startingPosition);

    // Main Game Loop
    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        // Physics Updates
        std::vector<Entity *> props = propManager->GetProps();
        player->TickPhysics(dt, player->GetWorldPosition(), worldMap->GetMapBounds(), props, true);
        propManager->TickPhysics(dt, player->GetWorldPosition(), worldMap->GetMapBounds());

        // Rendering
        BeginDrawing();

        ClearBackground(backgroundColor);
        worldMap->DrawWorldMap(Vector2Scale(player->GetWorldPosition(), -1.0)); // Flip player's world position to get map position
        propManager->TickAnimation();
        player->TickAnimation(true);

        EndDrawing();
        // Rendering Ends
    }

    delete worldMap;
    delete player;
    CloseWindow();
    return 0;
}
