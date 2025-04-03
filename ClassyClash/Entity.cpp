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
    
    worldPosition.x = gameDimensions.x/2 - frameRect.width/2;
    worldPosition.y = gameDimensions.y - frameRect.height;
    this->entityWidth = frameRect.width;
    this->entityHeight = frameRect.height;

    this->animationFramePeriod = (1.0 / animationFPS);
}

// Setters / Getters
void Entity::SetAnimationRate(float animationRate){ animationFramePeriod = 1.0 / animationRate; }
void Entity::SetAnimationFramePeriod(float animationFramePeriod){ this->animationFramePeriod = animationFramePeriod; }
Vector2 Entity::GetPosition() { return worldPosition; }
Rectangle Entity::GetPositionalRect(float pad) {
    Rectangle positionalRect{
        worldPosition.x + pad,
        worldPosition.y + pad,
        frameRect.width - 2*pad,
        frameRect.height - 2*pad
    };
    return positionalRect;
}

// Default Virtual Methods
void Entity::SetDeltaFrameTime(float frameTime){ this->frameTime = frameTime; }

// Other Methods
void Entity::OverridePosition(Vector2 newPosition) {
    worldPosition = newPosition;
}
void Entity::DrawEntity() {
    if (this->IsMoving()) { currentTexture2D = runTexture2D; }
    else { currentTexture2D = idleTexture2D; }

    // Flipping
    Rectangle frameRectLook{frameRect};
    if (this->IsLookingLeft()) { frameRectLook.width *= -1; }

    // Scaling
    Vector2 screenPosition = GetScreenPosition();
    float newWidth = frameRect.width * spriteScaler;
    float newHeight = frameRect.height * spriteScaler;
    Rectangle scaledFrameRect{
        screenPosition.x - newWidth / 2,
        screenPosition.y - newHeight / 2,
        newWidth,
        newHeight
    };

    DrawTexturePro(currentTexture2D, frameRectLook, scaledFrameRect, Vector2{0,0}, 0.0, WHITE);
}
