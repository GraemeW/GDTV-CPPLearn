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
    void UpdatePosition() override;
    void UpdateActions(Entity* player) override;
    void UpdateAnimationFrame() override;
    void DrawAccessories() override;

public:
    Prop(string texturePath, float padding, Vector2 gameDimensions, Vector2 worldPosition);
    void ApplyDamage(float damage) override;
};
#endif
