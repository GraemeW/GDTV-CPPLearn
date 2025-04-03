//
// PlayerMover.cpp
// ClassyClash
//

#include <string>
#include <iostream>
#include "PlayerMover.hpp"

Vector2 PlayerMover::GetPositionShift() {
    Vector2 positionShift{0.0, 0.0};
    bool hasMoved = false;

    // L/R
    if (IsKeyDown(KEY_A)) {
        positionShift = Vector2Add(positionShift, Vector2{speed * frameTime, 0.0});
        hasMoved = true;
    }
    if (IsKeyDown(KEY_D)) {
        positionShift = Vector2Subtract(positionShift, Vector2{speed * frameTime, 0.0});
        hasMoved = true;
    }

    // U/D
    if (IsKeyDown(KEY_W)) {
        positionShift = Vector2Add(positionShift, Vector2{0.0, speed * frameTime});
        hasMoved = true;
    }
    if (IsKeyDown(KEY_S)) {
        positionShift = Vector2Subtract(positionShift, Vector2{0.0, speed * frameTime});
        hasMoved = true;
    }

    isMoving = hasMoved;
    return positionShift;
}

bool PlayerMover::IsMoving() { return isMoving; }
