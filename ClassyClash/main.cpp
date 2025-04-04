#include "main.h"
#include <string>
#include <vector>

int main(int argc, char const *argv[])
{
    /* GAME CODE */
    // Initialization
    InitWindow(gameDimensions.x, gameDimensions.y, gameTitle.c_str());
    SetTargetFPS(targetFPS);
    WorldMap* worldMap = new WorldMap();
    Player* player = new Player(knightTexturePathActive, knightTexturePathIdle, knightxyFrameCount, gameDimensions, animationRate);
    player->OverridePosition(startingPosition);

    // Main Game Loop
    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        // Physics Updates
        player->TickPhysics(dt, player->GetWorldPosition(), worldMap->GetMapBounds(), true);

        // Rendering
        BeginDrawing();
        ClearBackground(backgroundColor);
        worldMap->DrawWorldMap(Vector2Scale(player->GetWorldPosition(), -1.0)); // Flip player's world position to get map position

        // Animatiton Updates
        player->TickAnimation();

        EndDrawing();
        // Rendering Ends
    }

    delete worldMap;
    delete player;
    CloseWindow();
    return 0;
}
