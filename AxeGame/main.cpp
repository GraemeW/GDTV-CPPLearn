#include "raylib.h"
#include <string>
#include <iostream>
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
    int circleRadius = 60;
    Color circleColor = BLUE;
    float circleMoveSpeed = 1000.0;

    int axeWidth = 50;
    int axeHeight = 75;
    Color rectangleColor = RED;
    float axeMoveSpeed = 500.0;

    // Derived Parameters
    int windowMidCol = round(gameWidth / 2);
    int windowMidRow = round(gameHeight / 2);

    // ***Execution***
    // Init Window/Settings
    InitWindow(gameWidth, gameHeight, gameTitle.c_str());
    SetTargetFPS(targetFPS);

    // Start points
    int circleRow = windowMidRow;
    int circleCol = 0;
    int axeRow = 0;
    int axeCol = windowMidCol;

    while (!WindowShouldClose())
    {
        // Game Logic
        // Circle Movement
        GetUserInputCol(circleMoveSpeed, circleCol, gameWidth, circleRadius);
        GetUserInputRow(circleMoveSpeed, circleRow, gameHeight, circleRadius);

        // Axe Movement
        int featureSize = round(axeHeight/2);
        GetTimeShiftedRow(axeMoveSpeed, axeRow, gameHeight, featureSize);

        // Check for collisions
        if (DidEntitiesCollide(circleRow, circleCol, circleRadius, axeRow, axeCol, axeWidth, axeHeight))
        {
            std::cout << "Player circle collided with axe!" << std::endl;
        }

        // Game Logic Ends
        BeginDrawing();
        ClearBackground(WHITE);
        DrawCircle(circleCol, circleRow, circleRadius, circleColor);
        DrawRectangle(axeCol, axeRow, axeWidth, axeHeight, rectangleColor);
        EndDrawing();
    }

    return 0;
}

void GetUserInputCol(float moveSpeed, int &inputCol, int gameWidth, int featureSize)
{
    int colOffset = 0;
    if (IsKeyDown(KEY_RIGHT)) { colOffset += (int)round(GetFrameTime() * moveSpeed); }
    if (IsKeyDown(KEY_LEFT)) { colOffset -= (int)round(GetFrameTime() * moveSpeed); }
    inputCol += colOffset;

    // Check for edges, loop around
    if (inputCol > (gameWidth + featureSize)) { inputCol = -featureSize; }
    else if (inputCol < -featureSize) { inputCol = gameWidth + featureSize; }
}

void GetUserInputRow(float moveSpeed, int &inputRow, int gameHeight, int featureSize)
{
    int rowOffset = 0;
    if (IsKeyDown(KEY_DOWN)) { rowOffset += (int)round(GetFrameTime() * moveSpeed); }
    if (IsKeyDown(KEY_UP)) { rowOffset -= (int)round(GetFrameTime() * moveSpeed); }
    inputRow += rowOffset;

    // Check for edges, loop around
    if (inputRow > (gameHeight + featureSize)) { inputRow = -featureSize; }
    else if (inputRow < -featureSize) { inputRow = gameHeight + featureSize; }
}

void GetTimeShiftedRow(float &moveSpeed, int &inputRow, int gameHeight, int featureSize)
{
    inputRow += (int)round(GetFrameTime() * moveSpeed);

    // Check for edges, flip direction
    if (inputRow > (gameHeight + featureSize) || (inputRow < -featureSize)) { moveSpeed = -moveSpeed; }
}

bool DidEntitiesCollide(int playerRow, int playerCol, int playerRadius, int axeRow, int axeCol, int axeWidth, int axeHeight)
{
    int playerLeftColBound, playerRightColBound, playerTopRowBound, playerBottomRowBound;
    int axeLeftColBound, axeRightColBound, axeTopRowBound, axeBottomRowBound;

    GetCircleBounds(playerCol, playerRow, playerRadius, playerLeftColBound, playerRightColBound, playerTopRowBound, playerBottomRowBound);
    GetRectangleBounds(axeCol, axeRow, axeWidth, axeHeight, axeLeftColBound, axeRightColBound, axeTopRowBound, axeBottomRowBound);

    bool colOverlap = (playerRightColBound > axeLeftColBound) && (playerLeftColBound < axeRightColBound);
    bool rowOverlap = (playerBottomRowBound > axeTopRowBound) && (playerTopRowBound < axeBottomRowBound);

    return (colOverlap && rowOverlap);
}

void GetCircleBounds(int col, int row, int radius, int &leftColBound, int &rightColBound, int &topRowBound, int &bottomRowBound)
{
    leftColBound = col - radius;
    rightColBound = col + radius;
    topRowBound = row - radius;
    bottomRowBound = row + radius;
}

void GetRectangleBounds(int col, int row, int width, int height, int &leftColBound, int &rightColBound, int &topRowBound, int &bottomRowBound)
{
    leftColBound = col;
    topRowBound = row;
    rightColBound = col + width;
    bottomRowBound = row + height;
}
