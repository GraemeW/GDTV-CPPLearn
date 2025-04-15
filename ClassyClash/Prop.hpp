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
    void Tick(Entity* player) override;
    void UpdatePosition() override;
    void UpdateAnimationFrame() override;

public:
    Prop(string texturePath, float padding, Vector2 gameDimensions, Vector2 worldPosition);
};
#endif
