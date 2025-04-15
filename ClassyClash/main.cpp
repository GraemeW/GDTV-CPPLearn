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
    PropSpawner* propSpawner = new PropSpawner(gameDimensions);
    EnemySpawner* enemySpawner = new EnemySpawner(gameDimensions, animationRate);
    Player* player = new Player(knightTexturePathActive, knightTexturePathIdle, knightxyFrameCount, knightPadding, gameDimensions, animationRate);
    player->OverridePosition(startingPosition);

    // Main Game Loop
    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        Entity::TickEntities(player);
        Entity::TickPhysicsEntities(dt, worldMap->GetMapBounds());

        BeginDrawing();
        ClearBackground(backgroundColor);
        worldMap->DrawWorldMap(Vector2Scale(player->GetWorldPosition(), -1.0)); // Flip player's world position to get map position
        Entity::TickAnimationEntities(player);
        EndDrawing();
    }

    delete worldMap;
    delete propSpawner;
    delete enemySpawner;
    delete player;
    CloseWindow();
    return 0;
}
