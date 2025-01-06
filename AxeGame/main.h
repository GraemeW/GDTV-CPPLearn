#pragma once
void GetUserInputCol(float circleMoveSpeed, int &circleCol, int gameWidth, int circleRadius);
void GetUserInputRow(float circleMoveSpeed, int &circleRow, int gameHeight, int circleRadius);
void GetTimeShiftedRow(float &moveSpeed, int &inputRow, int gameHeight, int featureSize);
bool DidEntitiesCollide(int playerRow, int playerCol, int playerRadius, int axeRow, int axeCol, int axeWidth, int axeHeight);
void GetCircleBounds(int col, int row, int radius, int &leftColBound, int &rightColBound, int &topRowBound, int &bottomRowBound);
void GetRectangleBounds(int col, int row, int width, int height, int &leftColBound, int &rightColBound, int &topRowBound, int &bottomRowBound);
