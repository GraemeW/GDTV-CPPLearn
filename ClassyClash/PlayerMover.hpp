//
// PlayerMover.h
// ClassyClash
//

#pragma once
using std::string;
#include <string>
#include "raylib.h"
#include "raymath.h"

#ifndef PlayerMover_h
#define PlayerMover_h
class PlayerMover
{
private:
    // Tunables
    float speed{350.0};

public:
    // Methods
    Vector2 GetVelocity();
};
#endif
