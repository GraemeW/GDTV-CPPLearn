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

    std::vector<Entity *> entities;
    entities.push_back(player);
    for (Entity* prop : propSpawner->GetProps()) { entities.push_back(prop); }
    for (Entity* enemy : enemySpawner->GetEnemies()) { entities.push_back(enemy); }

    // Main Game Loop
    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        // Behavioural Updates
        Entity::TickEntities(player);

        // Physics Updates
        player->TickPhysics(dt, worldMap->GetMapBounds(), entities, true);
        propSpawner->TickPhysics(dt, worldMap->GetMapBounds());
        enemySpawner->TickPhysics(dt, worldMap->GetMapBounds(), entities);

        // Rendering
        BeginDrawing();

        ClearBackground(backgroundColor);
        worldMap->DrawWorldMap(Vector2Scale(player->GetWorldPosition(), -1.0)); // Flip player's world position to get map position
        player->TickAnimation(player);
        propSpawner->TickAnimation(player);
        enemySpawner->TickAnimation(player);

        EndDrawing();
        // Rendering Ends
    }

    delete worldMap;
    delete propSpawner;
    delete enemySpawner;
    delete player;
    CloseWindow();
    return 0;
}
