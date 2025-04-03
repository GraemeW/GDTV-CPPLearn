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
        positionShift = Vector2Add(positionShift, Vector2{1.0, 0.0}); 
        hasMoved = true;  
        isLookingLeft = true;
    }
    if (IsKeyDown(KEY_D)) { 
        positionShift = Vector2Subtract(positionShift, Vector2{1.0, 0.0}); 
        hasMoved = true; 
        isLookingLeft = false;
    }

    // U/D
    if (IsKeyDown(KEY_W)) { positionShift = Vector2Add(positionShift, Vector2{0.0, 1.0}); hasMoved = true; }
    if (IsKeyDown(KEY_S)) { positionShift = Vector2Subtract(positionShift, Vector2{0.0, 1.0}); hasMoved = true; }

    isMoving = hasMoved;
    return Vector2Scale(Vector2Normalize(positionShift), speed * frameTime);
}

bool PlayerMover::IsMoving() { return isMoving; }
bool PlayerMover::IsLookingLeft() { return isLookingLeft; }
