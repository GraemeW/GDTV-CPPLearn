//
// Prop.cpp
// ClassyClash
//

#include <string>
#include <iostream>
#include "Prop.hpp"

Prop::Prop(string texturePath, float padding, Vector2 gameDimensions, Vector2 worldPosition) 
: Entity(texturePath, texturePath, (int[]){1,1}, padding, gameDimensions, 1.0) {
    this->entityType = EntityType::PropType;
    this->worldPosition = worldPosition;
}

// Unused for prop (unless we add prop animations in future)
void Prop::ApplyDamage(float damage) { }
void Prop::UpdatePosition() { }
void Prop::UpdateActions(Entity* player) { }
void Prop::UpdateAnimationFrame() { }
void Prop::DrawAccessories() { }
