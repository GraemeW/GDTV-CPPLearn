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
enum EntityType {
    PropType,
    EnemyType,
    PlayerType
};

class Entity
{
private:
    // Static
    static std::vector<Entity *> entities;

protected:
    virtual ~Entity();

    // Tunables
    float spriteScaler{4.0};
    float damageCooldown{1.5}; // seconds

    // Cached
    Texture2D runTexture2D;
    Texture2D idleTexture2D;
    float padding;
    Rectangle frameRect;
    Vector2 gameDimensions;
    float animationFramePeriod;

    // State
    EntityType entityType{};

    float frameTime{0};
    int animationFrame{0};
    float runningTime{0};
    float entityWidth{0};
    float entityHeight{0};
    Texture2D currentTexture2D;
    Color spriteColor{WHITE};
    Vector2 worldPosition{0,0};
    Vector2 velocity{};
    bool isLookingLeft;
    int healthFontSize = 24;
    Color healthFontColor = RED;

    bool isAlive{true};
    float hitPoints{1.0}; // Override in child constructor
    float damageCooldownTimer{0};

    // Methods
    // Ticks
    void Tick(Entity* player);
    void TickPhysics(float frameTime, Vector4 mapBounds);
    void TickAnimation(Entity* player);

    // Setters/Getters
    bool IsLookingLeft();
    bool IsMoving();
    void SetAnimationRate(float animationRate);
    void SetAnimationFramePeriod(float animationFramePeriod);
    Vector2 GetScreenPosition(Vector2 playerWorldPosition);

    // State Updates
    virtual void UpdatePosition() = 0;
    virtual void UpdateActions(Entity* player) = 0;
    virtual void UpdateAnimationFrame() = 0;
    void UpdateLookDirection();

    // Helpers
    void ClampPosition(Vector4 bounds);
    std::vector<Entity *> FindCollidingEntities(Rectangle collider);
    void DrawEntity(Entity* player);
    virtual void DrawAccessories() = 0;
    void DrawHealth(Entity* player);

public:
    Entity(string runTexturePath, string idleTexturePath, int xyFrameCount[2], float padding, Vector2 gameDimensions, float animationFPS);
    virtual void ApplyDamage(float damage) = 0;
    void OverridePosition(Vector2 newPosition);
    Vector2 GetWorldPosition();
    Rectangle GetCollider();
    EntityType GetEntityType() { return entityType; }
    bool IsAlive();

    // Static Class Behavior
    static void AddToEntities(Entity* entity);
    static void RemoveFromEntities(Entity* entity);
    static void DeleteAllEntities();
    static bool CheckCollisions(Entity* entity);
    static bool DeleteOverlappingEntity(Entity* entity);
    static void TickEntities(Entity* player);
    static void TickPhysicsEntities(float frameTime, Vector4 mapBounds);
    static void TickAnimationEntities(Entity* player);
};
#endif
