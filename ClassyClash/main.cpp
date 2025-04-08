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

    Enemy* enemy = new Enemy(goblinTexturePathActive, goblinTexturePathIdle, goblinxyFrameCount, goblinPadding, gameDimensions, animationRate, goblinStartingPosition);

    std::vector<Entity *> entities = propManager->GetProps();
    entities.push_back(enemy);
    entities.push_back(player);

    // Main Game Loop
    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        // Physics Updates
        player->TickPhysics(dt, player->GetWorldPosition(), worldMap->GetMapBounds(), entities, true);
        propManager->TickPhysics(dt, player->GetWorldPosition(), worldMap->GetMapBounds());
        enemy->TickPhysics(dt, player->GetWorldPosition(), worldMap->GetMapBounds(), entities, false);

        // Rendering
        BeginDrawing();

        ClearBackground(backgroundColor);
        worldMap->DrawWorldMap(Vector2Scale(player->GetWorldPosition(), -1.0)); // Flip player's world position to get map position
        propManager->TickAnimation();
        player->TickAnimation(true);
        enemy->TickAnimation(false);

        EndDrawing();
        // Rendering Ends
    }

    delete worldMap;
    delete player;
    CloseWindow();
    return 0;
}
