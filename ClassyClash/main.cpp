#include "main.h"
#include <string>
#include <vector>

int main(int argc, char const *argv[])
{
    /* GAME CODE */
    // Initialization
    InitWindow(gameDimensions[0], gameDimensions[1], gameTitle.c_str());
    SetTargetFPS(targetFPS);
    WorldMap* worldMap = new WorldMap();

    // Main Game Loop
    while (!WindowShouldClose()) {


        // Rendering
        BeginDrawing();
        ClearBackground(backgroundColor);
        worldMap->DrawWorldMap(startingPosition);

        EndDrawing();
        // Rendering Ends
    }

    delete worldMap;
    CloseWindow();
    return 0;
}
