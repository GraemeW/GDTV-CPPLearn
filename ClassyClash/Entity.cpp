//
// Entity.cpp
// ClassyClash
//

#include <string>
#include <iostream>
#include "Entity.hpp"

Entity::Entity(string runTexturePath, string idleTexturePath, int xyFrameCount[2], Vector2 gameDimensions, float animationFPS) {
    runTexture2D = LoadTexture(runTexturePath.c_str());
    idleTexture2D = LoadTexture(idleTexturePath.c_str());
    
    currentTexture2D = idleTexture2D;
    this->gameDimensions = gameDimensions;
    
    frameRect.width = currentTexture2D.width/xyFrameCount[0];
    frameRect.height = currentTexture2D.height/xyFrameCount[1];
    frameRect.x = 0;
    frameRect.y = 0;
    
    entityPosition.x = gameDimensions.x/2 - frameRect.width/2;
    entityPosition.y = gameDimensions.y - frameRect.height;
    this->entityWidth = frameRect.width;
    this->entityHeight = frameRect.height;

    this->animationFramePeriod = (1.0 / animationFPS);
}

// Setters / Getters
void Entity::SetAnimationRate(float animationRate){ animationFramePeriod = 1.0 / animationRate; }
void Entity::SetAnimationFramePeriod(float animationFramePeriod){ this->animationFramePeriod = animationFramePeriod; }
Vector2 Entity::GetPosition() { return entityPosition; }
Rectangle Entity::GetPositionalRect(float pad) {
    Rectangle positionalRect{
        entityPosition.x + pad,
        entityPosition.y + pad,
        frameRect.width - 2*pad,
        frameRect.height - 2*pad
    };
    return positionalRect;
}

// Default Virtual Methods
void Entity::SetDeltaFrameTime(float frameTime){ this->frameTime = frameTime; }

// Other Methods
void Entity::OverridePosition(Vector2 newPosition) {
    entityPosition = newPosition;
}
void Entity::DrawEntity(bool forceCentered) {
    if (isMoving) { currentTexture2D = runTexture2D; }
    else { currentTexture2D = idleTexture2D; }

    Vector2 drawPosition = entityPosition;
    if (forceCentered) { drawPosition = Vector2{gameDimensions.x/2,gameDimensions.y/2}; }

    // Scaling
    float newWidth = frameRect.width * spriteScaler;
    float newHeight = frameRect.height * spriteScaler;
    Rectangle scaledFrameRect{
        drawPosition.x - newWidth / 2,
        drawPosition.y - newHeight / 2,
        newWidth,
        newHeight
    };

    DrawTexturePro(currentTexture2D, frameRect, scaledFrameRect, Vector2{0,0}, 0.0, WHITE);
}
