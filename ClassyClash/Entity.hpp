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
    static std::vector<Entity *> entities;

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

    // Methods
    // Ticks
    virtual void Tick(Entity* player) = 0;
    virtual void TickPhysics(float frameTime, Vector4 mapBounds, std::vector<Entity *> entities, bool isPlayer = false);
    virtual void TickAnimation(Entity* player);

    // Setters/Getters
    virtual void SetDependentFrameTime(float frameTime) = 0;
    virtual bool IsMoving() = 0;
    virtual bool IsLookingLeft() = 0;

    // State Updates
    virtual void UpdatePosition(std::vector<Entity *> otherEntities) = 0;
    virtual void UpdateAnimationFrame() = 0;

    // Helpers
    void ClampPosition(Vector4 bounds);
    bool CheckCollisions(std::vector<Entity *> entities);
    void DrawEntity(Entity* player);

public:
    Entity(string runTexturePath, string idleTexturePath, int xyFrameCount[2], float padding, Vector2 gameDimensions, float animationFPS);

    // Setters & Getters
    void SetAnimationRate(float animationRate);
    void SetAnimationFramePeriod(float animationFramePeriod);
    Vector2 GetWorldPosition();
    Rectangle GetCollider();

    // Methods
    void OverridePosition(Vector2 newPosition);
    Vector2 GetScreenPosition(Vector2 playerWorldPosition, bool isPlayer = false);

    // Static Class Behavior
    static void AddToEntities(Entity* entity);
    static void TickEntities(Entity* player);
    static void TickPhysicsEntities(float frameTime, Vector4 mapBounds, std::vector<Entity *> entities, bool isPlayer = false);
    static void TickAnimationEntities(Entity* player);

};
#endif
