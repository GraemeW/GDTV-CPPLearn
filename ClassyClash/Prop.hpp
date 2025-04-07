//
// Prop.h
// ClassyClash
//

#pragma once
using std::string;
#include <string>
#include "raylib.h"
#include "raymath.h"
#include "Entity.hpp"

#ifndef Prop_h
#define Prop_h
class Prop : public Entity
{
protected:
    // Virtual Methods
    void SetDependentFrameTime(float frameTime) override;
    void UpdatePosition(std::vector<Rectangle> colliders) override;
    void UpdateAnimationFrame() override;
    bool IsMoving() override;
    bool IsLookingLeft() override;

public:
    Prop(string texturePath, float padding, Vector2 gameDimensions, Vector2 worldPosition);
};
#endif
