//
// Prop.cpp
// ClassyClash
//

#include <string>
#include <iostream>
#include "Prop.hpp"

Prop::Prop(string texturePath, Vector2 gameDimensions, Vector2 worldPosition) 
: Entity(texturePath, texturePath, (int[]){1,1}, gameDimensions, 1.0) {
    currentTexture2D = idleTexture2D; // No state on props

    this->gameDimensions = gameDimensions;
    
    frameRect.width = currentTexture2D.width;
    frameRect.height = currentTexture2D.height;
    frameRect.x = 0;
    frameRect.y = 0;

    this->worldPosition = worldPosition;
    this->entityWidth = frameRect.width;
    this->entityHeight = frameRect.height;
}

// Unused for prop (unless we add prop animations in future)
void Prop::SetDependentFrameTime(float frameTime) { }
void Prop::UpdatePosition() { }
void Prop::UpdateAnimationFrame() { }

// Simple Overrides -- No look, move for props
bool Prop::IsMoving() { return false; }
bool Prop::IsLookingLeft() { return false; }
