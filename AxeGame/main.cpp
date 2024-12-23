#include "raylib.h"
#include <string>

int main(int argc, char const *argv[])
{
    // Tunables
    int gameWidth = 800;
    int gameHeight = 600;
    std::string gameTitle = "Axe Game";
    int targetFPS = 60;

    int circleRadius = 100;
    Color circleColor = BLUE;
    float circleMoveSpeed = 1000.0;

    // Derived Parameters
    int windowMidCol = round(gameWidth / 2);
    int windowMidRow = round(gameHeight / 2);

    // Execution
    // Init Window/Settings
    InitWindow(gameWidth, gameHeight, gameTitle.c_str());
    SetTargetFPS(targetFPS);

    // Circle start point 
    int circleRow = windowMidRow;
    int circleCol = windowMidCol;
    while (!WindowShouldClose())
    {
        // Traverse to right, reset to left
        if (circleCol < (gameWidth+circleRadius)) { circleCol += (int)round(GetFrameTime() * circleMoveSpeed); }
        else { circleCol = -circleRadius; }

        BeginDrawing();
        ClearBackground(WHITE);
        DrawCircle(circleCol, circleRow, circleRadius, circleColor);
        EndDrawing();
    }

    return 0;
}

