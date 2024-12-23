#include "raylib.h"
#include <string>
#include "main.h"

int main(int argc, char const *argv[])
{
    // ***Tunables***
    // Window + Game Settings
    int gameWidth = 800;
    int gameHeight = 600;
    std::string gameTitle = "Axe Game";
    int targetFPS = 60;

    // Characters
    int circleRadius = 100;
    Color circleColor = BLUE;
    float circleMoveSpeed = 1000.0;

    // Derived Parameters
    int windowMidCol = round(gameWidth / 2);
    int windowMidRow = round(gameHeight / 2);

    // ***Execution***
    // Init Window/Settings
    InitWindow(gameWidth, gameHeight, gameTitle.c_str());
    SetTargetFPS(targetFPS);

    // Circle start point 
    int circleRow = windowMidRow;
    int circleCol = windowMidCol;
    while (!WindowShouldClose())
    {
        GetUserInputCircleCol(circleMoveSpeed, circleCol, gameWidth, circleRadius);
        GetUserInputCircleRow(circleMoveSpeed, circleRow, gameHeight, circleRadius);

        BeginDrawing();
        ClearBackground(WHITE);
        DrawCircle(circleCol, circleRow, circleRadius, circleColor);
        EndDrawing();
    }

    return 0;
}

void GetUserInputCircleCol(float circleMoveSpeed, int &circleCol, int gameWidth, int circleRadius)
{
    int colOffset = 0;
    if (IsKeyDown(KEY_RIGHT)) { colOffset += (int)round(GetFrameTime() * circleMoveSpeed); }
    if (IsKeyDown(KEY_LEFT)) { colOffset -= (int)round(GetFrameTime() * circleMoveSpeed); }
    circleCol += colOffset;

    // Check for edges, loop around
    if (circleCol > gameWidth + circleRadius) { circleCol = -circleRadius; }
    else if (circleCol < -circleRadius) { circleCol = gameWidth + circleRadius; }
}

void GetUserInputCircleRow(float circleMoveSpeed, int &circleRow, int gameHeight, int circleRadius)
{
    int rowOffset = 0;
    if (IsKeyDown(KEY_DOWN)) { rowOffset += (int)round(GetFrameTime() * circleMoveSpeed); }
    if (IsKeyDown(KEY_UP)) { rowOffset -= (int)round(GetFrameTime() * circleMoveSpeed); }
    circleRow += rowOffset;

    // Check for edges, loop around
    if (circleRow > gameHeight + circleRadius) { circleRow = -circleRadius; }
    else if (circleRow < -circleRadius) { circleRow = gameHeight + circleRadius; }
}
