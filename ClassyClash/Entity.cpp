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
    Entity::AddToEntities(this);
    
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
void Entity::AddToEntities(Entity* entity) { entities.push_back(entity); }
void Entity::RemoveFromEntities(Entity* entity) {
    entities.erase(std::remove(entities.begin(), entities.end(), entity), entities.end());
}
void Entity::DeleteAllEntities() {
    for (int i = 0; i < entities.size(); i++) {
        if (entities[i] == nullptr) { continue; }
        delete entities[i];
    }
}

bool Entity::DeleteOverlappingEntity(Entity* entity) {
    if (CheckCollisions(entity)) {
        Entity::RemoveFromEntities(entity);
        delete entity;
        return true;
    }
    return false;
}

void Entity::TickEntities(Entity* player) {
    for (Entity* entity : entities) {
        if (entity == nullptr) { continue; }
        if (!entity->IsAlive()) { continue; }

        entity->Tick(player);
    }
}
void Entity::TickPhysicsEntities(float frameTime, Vector4 mapBounds) {
    for (Entity* entity : entities) {
        if (entity == nullptr) { continue; }
        if (!entity->IsAlive()) { continue; }

        entity->TickPhysics(frameTime, mapBounds);
    }
}
void Entity::TickAnimationEntities(Entity* player) {
    for (Entity* entity : entities) {
        if (entity == nullptr) { continue; }
        if (!entity->IsAlive()) { continue; }

        entity->TickAnimation(player);
    }
}

// Setters / Getters
bool Entity::IsMoving() {
    float currentSpeed = abs(Vector2Length(velocity));
    return (currentSpeed > 0.0);
}

bool Entity::IsAlive() { return isAlive; }

bool Entity::IsLookingLeft() { return isLookingLeft; }

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
void Entity::Tick(Entity* player) {
    UpdateActions(player);
}

void Entity::TickPhysics(float frameTime, Vector4 mapBounds) { 
    this->frameTime = frameTime;
    if (damageCooldownTimer > 0.0) { damageCooldownTimer -= frameTime; }

    UpdatePosition();
    ClampPosition(mapBounds);
    UpdateLookDirection();
}

void Entity::TickAnimation(Entity* player) {
    UpdateAnimationFrame();
    DrawEntity(player);
}

void Entity::UpdateLookDirection() {
    float xAxisSpeed = Vector2DotProduct(velocity, Vector2{1.0, 0.0});
    if (abs(xAxisSpeed) > 0) {
        isLookingLeft = xAxisSpeed < 0.0;
    }
}

void Entity::ClampPosition(Vector4 bounds) {
    // Bounds follow:  W/S/N/E
    if (worldPosition.x < bounds.x) { worldPosition.x = bounds.x; }
    if (worldPosition.y > bounds.y) { worldPosition.y = bounds.y; }
    if (worldPosition.y < bounds.z) { worldPosition.y = bounds.z; }
    if (worldPosition.x > bounds.w) { worldPosition.x = bounds.w; }
}

bool Entity::CheckCollisions(Entity* entity) {
    for (Entity* opponentEntity : entities) {
        if (opponentEntity == entity) { continue; } // Do not collide with self

        // Only collide with props
        if (opponentEntity->GetEntityType() == EntityType::PropType) {
            if (CheckCollisionRecs(entity->GetCollider(), opponentEntity->GetCollider())) {  return true; }
        }
    }
    return false;
}

std::vector<Entity *> Entity::FindCollidingEntities(Rectangle collider) {
    std::vector<Entity *> collidingEntities;
    for (Entity* entity : entities) {
        if (entity == this) { continue; } // Do not collide with self
        if (CheckCollisionRecs(collider, entity->GetCollider())) { collidingEntities.push_back(entity); }
    }
    return collidingEntities;
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

    DrawTexturePro(currentTexture2D, frameRectLook, scaledFrameRect, Vector2{}, 0.0, spriteColor);
    DrawAccessories();

    if (entityType != EntityType::PropType) {
        DrawHealth(player);
    }
}

void Entity::DrawHealth(Entity* player) {
    std::string hitPointString = "";
    hitPointString.append(std::to_string(hitPoints), 0, 2);

    Vector2 textPosition = GetScreenPosition(player->GetWorldPosition());
    textPosition.y -= frameRect.height * 0.5;
    textPosition.x += frameRect.width;
    DrawText(hitPointString.c_str(), textPosition.x, textPosition.y, healthFontSize, healthFontColor);
}

void Entity::OverridePosition(Vector2 newPosition) {
    worldPosition = newPosition;
}

Vector2 Entity::GetScreenPosition(Vector2 playerWorldPosition) {
    Vector2 screenCenter = Vector2{gameDimensions.x/2,gameDimensions.y/2};

    Vector2 offset = Vector2Subtract(worldPosition, playerWorldPosition);
    return Vector2Add(screenCenter, offset);
}
