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
    player->AddWeapon(weaponTexturePath, WeaponTexturePathActive);

    // Main Game Loop
    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        Entity::TickEntities(player);
        enemySpawner->SpawnTick(dt);
        Entity::TickPhysicsEntities(dt, worldMap->GetMapBounds());

        BeginDrawing();
        ClearBackground(backgroundColor);
        worldMap->DrawWorldMap(player->GetWorldPosition());
        Entity::TickAnimationEntities(player);
        EndDrawing();
    }

    delete worldMap;
    delete propSpawner;
    delete enemySpawner;
    Entity::DeleteAllEntities();
    CloseWindow();
    return 0;
}
