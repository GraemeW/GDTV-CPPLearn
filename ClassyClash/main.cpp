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
    Player* player = new Player(knightTexturePathActive, knightTexturePathIdle, knightxyFrameCount, knightPadding, gameDimensions, animationRate, playerHitpoints);
    player->OverridePosition(startingPosition);
    player->AddWeapon(weaponTexturePath, WeaponTexturePathActive);

    ScoreBoard* scoreBoard = new ScoreBoard(0, player, gameDimensions);

    PropSpawner* propSpawner = new PropSpawner(gameDimensions);
    EnemySpawner* enemySpawner = new EnemySpawner(gameDimensions, animationRate, scoreBoard);

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
        scoreBoard->TickScore();
        EndDrawing();
    }

    delete worldMap;
    delete scoreBoard;
    delete propSpawner;
    delete enemySpawner;
    Entity::DeleteAllEntities();
    CloseWindow();
    return 0;
}
