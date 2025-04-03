//
// Entity.h
// ClassyClash
//

#pragma once
using std::string;
#include <string>
#include "raylib.h"

#ifndef Entity_h
#define Entity_h
class Entity
{
protected:
    virtual ~Entity() {UnloadTexture(currentTexture2D);};

    // Tunables
    float spriteScaler = 2.0;

    // Cached
    Texture2D runTexture2D;
    Texture2D idleTexture2D;
    Texture2D currentTexture2D;
    Rectangle frameRect;
    Vector2 gameDimensions;
    float animationFramePeriod;

    // State
    float frameTime{0};
    int animationFrame{0};
    float runningTime{0};

public:
    Entity(string runTexturePath, string idleTexturePath, int xyFrameCount[2], Vector2 gameDimensions, float animationFPS);

    // State
    Vector2 entityPosition;
    int entityWidth;
    int entityHeight;
    bool isMoving{false};

    // Setters & Getters
    void SetAnimationRate(float animationRate);
    void SetAnimationFramePeriod(float animationFramePeriod);
    Vector2 GetPosition();
    Rectangle GetPositionalRect(float pad = 0);

    // Default Virtual Methods
    virtual void SetDeltaFrameTime(float frameTime);

    // Pure Virtual Methods
    virtual void UpdatePosition() = 0;
    virtual void UpdateAnimationFrame() = 0;

    // Other Methods
    void DrawEntity(bool forceCentered = false);
    void OverridePosition(Vector2 newPosition);
};
#endif
