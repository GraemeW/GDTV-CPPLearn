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
private:
    // Static
    static std::vector<Entity *> entities;

protected:
    virtual ~Entity();

    // Tunables
    float spriteScaler{4.0};

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
    Vector2 velocity{};
    bool isLookingLeft;

    // Methods
    // Ticks
    virtual void Tick(Entity* player) = 0;
    void TickPhysics(float frameTime, Vector4 mapBounds);
    void TickAnimation(Entity* player);

    // Setters/Getters
    bool IsLookingLeft();
    bool IsMoving();
    void SetAnimationRate(float animationRate);
    void SetAnimationFramePeriod(float animationFramePeriod);
    Rectangle GetCollider();
    Vector2 GetScreenPosition(Vector2 playerWorldPosition, bool isPlayer = false);

    // State Updates
    virtual void UpdatePosition() = 0;
    virtual void UpdateActions() = 0;
    virtual void UpdateAnimationFrame() = 0;
    virtual void DrawAccessories() = 0;
    void UpdateLookDirection();

    // Helpers
    void ClampPosition(Vector4 bounds);
    bool CheckCollisions(Rectangle collider);
    void DrawEntity(Entity* player);

public:
    Entity(string runTexturePath, string idleTexturePath, int xyFrameCount[2], float padding, Vector2 gameDimensions, float animationFPS);
    void OverridePosition(Vector2 newPosition);
    Vector2 GetWorldPosition();

    // Static Class Behavior
    static void AddToEntities(Entity* entity);
    static void TickEntities(Entity* player);
    static void TickPhysicsEntities(float frameTime, Vector4 mapBounds);
    static void TickAnimationEntities(Entity* player);
};
#endif
