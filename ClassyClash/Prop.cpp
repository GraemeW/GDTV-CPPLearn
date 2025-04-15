//
// Prop.cpp
// ClassyClash
//

#include <string>
#include <iostream>
#include "Prop.hpp"

Prop::Prop(string texturePath, float padding, Vector2 gameDimensions, Vector2 worldPosition) 
: Entity(texturePath, texturePath, (int[]){1,1}, padding, gameDimensions, 1.0) {
    this->worldPosition = worldPosition;
}

// Unused for prop (unless we add prop animations in future)
void Prop::SetDependentFrameTime(float frameTime) { }
void Prop::Tick(Entity* player) { }
void Prop::UpdatePosition() { }
void Prop::UpdateAnimationFrame() { }

// Simple Overrides -- No look, move for props
bool Prop::IsMoving() { return false; }
bool Prop::IsLookingLeft() { return false; }
