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
    EnemyManager* enemyManager = new EnemyManager(gameDimensions, animationRate);
    Player* player = new Player(knightTexturePathActive, knightTexturePathIdle, knightxyFrameCount, knightPadding, gameDimensions, animationRate);
    player->OverridePosition(startingPosition);

    std::vector<Entity *> entities;
    entities.push_back(player);
    for (Entity* prop : propManager->GetProps()) { entities.push_back(prop); }
    for (Entity* enemy : enemyManager->GetEnemies()) { entities.push_back(enemy); }

    // Main Game Loop
    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        // Physics Updates
        player->TickPhysics(dt, player->GetWorldPosition(), worldMap->GetMapBounds(), entities, true);
        propManager->TickPhysics(dt, player->GetWorldPosition(), worldMap->GetMapBounds());
        enemyManager->TickPhysics(dt, player->GetWorldPosition(), worldMap->GetMapBounds(), entities);

        // Rendering
        BeginDrawing();

        ClearBackground(backgroundColor);
        worldMap->DrawWorldMap(Vector2Scale(player->GetWorldPosition(), -1.0)); // Flip player's world position to get map position
        propManager->TickAnimation();
        player->TickAnimation(true);
        enemyManager->TickAnimation();

        EndDrawing();
        // Rendering Ends
    }

    delete worldMap;
    delete propManager;
    delete enemyManager;
    delete player;
    CloseWindow();
    return 0;
}
