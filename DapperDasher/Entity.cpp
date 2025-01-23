//
// Entity.cpp
// DapperDasher
//

#include <string>
#include <iostream>
#include "Entity.hpp"

Entity::Entity(string texturePath, int xFrameCount, int yFrameCount, int gameWidth, int gameHeight, float animationFPS) {
    texture2D = LoadTexture(texturePath.c_str());
    this->gameWidth = gameWidth;
    this->gameHeight = gameHeight;
    
    frameRect.width = texture2D.width/xFrameCount;
    frameRect.height = texture2D.height/yFrameCount;
    frameRect.x = 0;
    frameRect.y = 0;
    
    entityPosition.x = gameWidth/2 - frameRect.width/2;
    entityPosition.y = gameHeight - frameRect.height;
    this->entityWidth = frameRect.width;
    this->entityHeight = frameRect.height;

    this->animationFramePeriod = (1.0 / animationFPS);
}

Entity::~Entity() {
    std::cout << "Butthead";
    UnloadTexture(texture2D);
}

void Entity::SetAnimationRate(float animationRate){ animationFramePeriod = 1.0 / animationRate; }
void Entity::SetAnimationFramePeriod(float animationFramePeriod){ this->animationFramePeriod = animationFramePeriod; }
float Entity::GetScaledFrameTime(float frameTime) { return (frameTime * frameTimeScaler); }

void Entity::OverridePosition(float xPosition, float yPosition) {
    entityPosition.x = xPosition;
    entityPosition.y = yPosition;
}

void Entity::DrawEntity() {
    DrawTextureRec(texture2D, frameRect, entityPosition, WHITE);
}
