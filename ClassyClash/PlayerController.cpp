//
// PlayerMover.cpp
// ClassyClash
//

#include <string>
#include <iostream>
#include "PlayerController.hpp"

Vector2 PlayerController::GetVelocity() {
    Vector2 velocity{0.0, 0.0};

    // L/R
    if (IsKeyDown(KEY_A)) { velocity = Vector2Subtract(velocity, Vector2{1.0, 0.0}); }
    if (IsKeyDown(KEY_D)) { velocity = Vector2Add(velocity, Vector2{1.0, 0.0}); }

    // U/D
    if (IsKeyDown(KEY_W)) { velocity = Vector2Subtract(velocity, Vector2{0.0, 1.0}); }
    if (IsKeyDown(KEY_S)) { velocity = Vector2Add(velocity, Vector2{0.0, 1.0}); }

    return Vector2Scale(Vector2Normalize(velocity), speed);
}

bool PlayerController::IsAttacking() {
    return IsKeyDown(KEY_SPACE);
}
