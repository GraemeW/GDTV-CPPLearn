//
// Entity.h
// ClassyClash
//

#pragma once
using std::string;
#include <string>
#include "raylib.h"
#include "raymath.h"

#ifndef Entity_h
#define Entity_h
class Entity
{
protected:
    virtual ~Entity() {UnloadTexture(currentTexture2D);};

    // Tunables
    float spriteScaler = 4.0;

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
    Vector2 playerWorldPosition{0,0};

    // Methods
    virtual void SetDependentFrameTime(float frameTime) = 0;
    virtual void UpdatePosition() = 0;
    virtual void UpdateAnimationFrame() = 0;
    virtual bool IsMoving() = 0;
    virtual bool IsLookingLeft() = 0;
    void ClampPosition(Vector4 bounds);
    void DrawEntity();

public:
    Entity(string runTexturePath, string idleTexturePath, int xyFrameCount[2], Vector2 gameDimensions, float animationFPS);

    // State
    Vector2 worldPosition;
    int entityWidth;
    int entityHeight;

    // Setters & Getters
    void SetAnimationRate(float animationRate);
    void SetAnimationFramePeriod(float animationFramePeriod);
    Vector2 GetWorldPosition();
    Rectangle GetWorldPositionRect(float pad = 0);

    // Methods
    void TickPhysics(float frameTime, Vector2 playerWorldPosition, Vector4 mapBounds, bool setPlayerPositionToSelf = false);
    void TickAnimation();
    void OverridePosition(Vector2 newPosition);
    Vector2 GetScreenPosition(Vector2 playerWorldPosition);
};
#endif
