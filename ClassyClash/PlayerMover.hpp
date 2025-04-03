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
    float speed{100.0};

    // State
    float frameTime{0};
    bool isMoving{false};

public:
    // Methods
    void SetDeltaFrameTime(float frameTime){ this->frameTime = frameTime; }
    Vector2 GetPositionShift();
    bool IsMoving();
};
#endif
