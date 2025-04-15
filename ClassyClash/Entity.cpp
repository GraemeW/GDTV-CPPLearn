//
// Entity.cpp
// ClassyClash
//

#include <string>
#include "Entity.hpp"

// Static
std::vector<Entity*> Entity::entities;

// Methods
Entity::Entity(string runTexturePath, string idleTexturePath, int xyFrameCount[2], float padding, Vector2 gameDimensions, float animationFPS)
: padding(padding), gameDimensions(gameDimensions), animationFramePeriod(1.0 / animationFPS) {
    entities.push_back(this);

    //Entity::AddToEntities(this);
    
    runTexture2D = LoadTexture(runTexturePath.c_str());
    idleTexture2D = LoadTexture(idleTexturePath.c_str());
    
    currentTexture2D = idleTexture2D;
    
    frameRect.width = currentTexture2D.width/xyFrameCount[0];
    frameRect.height = currentTexture2D.height/xyFrameCount[1];
    frameRect.x = 0;
    frameRect.y = 0;
    
    worldPosition = Vector2{};
    this->entityWidth = frameRect.width * spriteScaler;
    this->entityHeight = frameRect.height * spriteScaler;
}

Entity::~Entity() {
    if (IsTextureValid(runTexture2D)) { UnloadTexture(runTexture2D); }
    if (IsTextureValid(idleTexture2D)) { UnloadTexture(idleTexture2D); }
}

// Static Methods
void Entity::AddToEntities(Entity* entity) {
    entities.push_back(entity);
}
void Entity::TickEntities(Entity* player) {
    for (Entity* entity : entities) {
        if (entity == nullptr) { continue; }
        entity->Tick(player);
    }
}
void Entity::TickPhysicsEntities(float frameTime, Vector4 mapBounds, std::vector<Entity *> entities, bool isPlayer) {}
void Entity::TickAnimationEntities(Entity* player) {}

// Setters / Getters
void Entity::SetAnimationRate(float animationRate){ animationFramePeriod = 1.0 / animationRate; }

void Entity::SetAnimationFramePeriod(float animationFramePeriod){ this->animationFramePeriod = animationFramePeriod; }

Vector2 Entity::GetWorldPosition() { return worldPosition; }

Rectangle Entity::GetCollider() {
    Rectangle positionalRect{
        worldPosition.x + padding,
        worldPosition.y + padding,
        entityWidth - 2*padding,
        entityHeight - 2*padding
    };
    return positionalRect;
}

// Default Methods
void Entity::TickPhysics(float frameTime, Vector4 mapBounds, std::vector<Entity *> entities, bool isPlayer) { 
    SetDependentFrameTime(frameTime);
    
    UpdatePosition(entities);
    ClampPosition(mapBounds);
}

void Entity::TickAnimation(Entity* player) {
    UpdateAnimationFrame();
    DrawEntity(player);
}

void Entity::ClampPosition(Vector4 bounds) {
    // Bounds follow:  W/S/N/E
    if (worldPosition.x < bounds.x) { worldPosition.x = bounds.x; }
    if (worldPosition.y > bounds.y) { worldPosition.y = bounds.y; }
    if (worldPosition.y < bounds.z) { worldPosition.y = bounds.z; }
    if (worldPosition.x > bounds.w) { worldPosition.x = bounds.w; }
}

bool Entity::CheckCollisions(std::vector<Entity *> entities) {
    for (Entity* entity : entities) {
        if (entity == this) { continue; } // Do not collide with self
        if (CheckCollisionRecs(this->GetCollider(), entity->GetCollider())) {  return true; }
    }
    return false;
}

void Entity::DrawEntity(Entity* player) {
    // Early returns if no reason to render
    if (this != player) { // Note:  always render player
        Vector2 deltaPosition = Vector2Subtract(worldPosition, player->GetWorldPosition());
        if (abs(deltaPosition.x) > gameDimensions.x || abs(deltaPosition.y) > gameDimensions.y) { return; }
    }
    
    // Texture Swaps
    if (this->IsMoving()) { currentTexture2D = runTexture2D; }
    else { currentTexture2D = idleTexture2D; }

    // Flipping
    Rectangle frameRectLook{frameRect};
    if (this->IsLookingLeft()) { frameRectLook.width *= -1; }

    // Scaling
    Vector2 screenPosition = GetScreenPosition(player->GetWorldPosition());
    Rectangle scaledFrameRect{
        screenPosition.x, screenPosition.y, entityWidth, entityHeight
    };

    DrawTexturePro(currentTexture2D, frameRectLook, scaledFrameRect, Vector2{}, 0.0, WHITE);
}

void Entity::OverridePosition(Vector2 newPosition) {
    worldPosition = newPosition;
}

Vector2 Entity::GetScreenPosition(Vector2 playerWorldPosition, bool isPlayer) {
    Vector2 screenCenter = Vector2{gameDimensions.x/2,gameDimensions.y/2};
    if (isPlayer) { return Vector2Subtract(screenCenter, Vector2{entityWidth/2, entityHeight/2}); }

    Vector2 offset = Vector2Subtract(worldPosition, playerWorldPosition);
    return Vector2Add(screenCenter, offset);
}
