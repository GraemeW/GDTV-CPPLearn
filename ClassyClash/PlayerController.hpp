//
// PlayerController.h
// ClassyClash
//

#pragma once
using std::string;
#include <string>
#include "raylib.h"
#include "raymath.h"

#ifndef PlayerController_h
#define PlayerController_h
class PlayerController
{
private:
    // Tunables
    float speed{350.0};

public:
    // Methods
    Vector2 GetVelocity();
    bool IsAttacking();
};
#endif
