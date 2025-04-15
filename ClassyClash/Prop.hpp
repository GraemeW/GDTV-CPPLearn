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
    void Tick(Entity* player) override;
    void UpdatePosition(std::vector<Entity *> entities) override;
    void UpdateAnimationFrame() override;
    bool IsMoving() override;
    bool IsLookingLeft() override;

public:
    Prop(string texturePath, float padding, Vector2 gameDimensions, Vector2 worldPosition);
    void TickPhysics(float frameTime, Vector4 mapBounds, std::vector<Entity *> entities, bool isPlayer = false) override;
    void TickAnimation(Entity* player) override;
};
#endif
