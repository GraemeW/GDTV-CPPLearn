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
        player->TickPhysics(dt, player->GetWorldPosition(), true);

        // Rendering
        BeginDrawing();
        ClearBackground(backgroundColor);
        worldMap->DrawWorldMap(player->GetWorldPosition());

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
