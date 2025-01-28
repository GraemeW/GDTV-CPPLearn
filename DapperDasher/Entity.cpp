//
// Entity.cpp
// DapperDasher
//

#include <string>
#include <iostream>
#include "Entity.hpp"

Entity::Entity(string texturePath, int xyFrameCount[2], const int gameDimensions[2], float animationFPS) {
    texture2D = LoadTexture(texturePath.c_str());
    this->gameWidth = gameDimensions[0];
    this->gameHeight = gameDimensions[1];
    
    frameRect.width = texture2D.width/xyFrameCount[0];
    frameRect.height = texture2D.height/xyFrameCount[1];
    frameRect.x = 0;
    frameRect.y = 0;
    
    entityPosition.x = gameWidth/2 - frameRect.width/2;
    entityPosition.y = gameHeight - frameRect.height;
    this->entityWidth = frameRect.width;
    this->entityHeight = frameRect.height;

    this->animationFramePeriod = (1.0 / animationFPS);
}

void Entity::SetDeltaFrameTime(float frameTime){ this->frameTime = frameTime; }
void Entity::SetAnimationRate(float animationRate){ animationFramePeriod = 1.0 / animationRate; }
void Entity::SetAnimationFramePeriod(float animationFramePeriod){ this->animationFramePeriod = animationFramePeriod; }
float Entity::GetScaledFrameTime() { return (frameTime * frameTimeScaler); }

void Entity::OverridePosition(int newPosition[2]) {
    entityPosition.x = newPosition[0];
    entityPosition.y = newPosition[1];
}

void Entity::DrawEntity() {
    DrawTextureRec(texture2D, frameRect, entityPosition, WHITE);
}
