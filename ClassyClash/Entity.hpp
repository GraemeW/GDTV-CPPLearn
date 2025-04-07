//
// Entity.h
// ClassyClash
//

#pragma once
using std::string;
#include <string>
#include <vector>
#include "raylib.h"
#include "raymath.h"

#ifndef Entity_h
#define Entity_h
class Entity
{
protected:
    virtual ~Entity();

    // Tunables
    float spriteScaler = 4.0;

    // Cached
    Texture2D runTexture2D;
    Texture2D idleTexture2D;
    float padding;
    Rectangle frameRect;
    Vector2 gameDimensions;
    float animationFramePeriod;

    // State
    float frameTime{0};
    int animationFrame{0};
    float runningTime{0};
    float entityWidth{0};
    float entityHeight{0};
    Texture2D currentTexture2D;
    Vector2 worldPosition{0,0};
    Vector2 playerWorldPosition{0,0};

    // Methods
    virtual void SetDependentFrameTime(float frameTime) = 0;
    virtual void UpdatePosition(std::vector<Rectangle> colliders) = 0;
    virtual void UpdateAnimationFrame() = 0;
    virtual bool IsMoving() = 0;
    virtual bool IsLookingLeft() = 0;
    void ClampPosition(Vector4 bounds);
    void DrawEntity(bool isPlayer = false);

public:
    Entity(string runTexturePath, string idleTexturePath, int xyFrameCount[2], float padding, Vector2 gameDimensions, float animationFPS);

    // Setters & Getters
    void SetAnimationRate(float animationRate);
    void SetAnimationFramePeriod(float animationFramePeriod);
    Vector2 GetWorldPosition();
    Rectangle GetCollider();

    // Methods
    void TickPhysics(float frameTime, Vector2 playerWorldPosition, Vector4 mapBounds, std::vector<Rectangle> colliders, bool isPlayer = false);
    void TickAnimation(bool isPlayer = false);
    void OverridePosition(Vector2 newPosition);
    Vector2 GetScreenPosition(Vector2 playerWorldPosition, bool isPlayer = false);
};
#endif
