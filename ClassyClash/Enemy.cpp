//
// Enemy.cpp
// ClassyClash
//

#include <string>
#include "Enemy.hpp"

// Methods
Enemy::Enemy(string runTexturePath, string idleTexturePath, int xyFrameCount[2], float padding, Vector2 gameDimensions, float animationFPS, Vector2 worldPosition) 
: Entity(runTexturePath, idleTexturePath, xyFrameCount, padding, gameDimensions, animationFPS) {
    this->worldPosition = worldPosition;
}

void Enemy::SetDependentFrameTime(float frameTime) { this->frameTime = frameTime; }
bool Enemy::IsMoving() { return isMoving; }
bool Enemy::IsLookingLeft() { return isLookingLeft; }

void Enemy::UpdatePosition(std::vector<Entity *> entities) {
    float playerDistanceSq = Vector2DistanceSqr(worldPosition, playerWorldPosition);
    if (playerDistanceSq > aggroRadiusSq) { return; }

    Vector2 oldWorldPosition = Vector2(worldPosition);
    Vector2 playerDirection = Vector2Subtract(playerWorldPosition, worldPosition);
    Vector2 positionShift = Vector2Scale(Vector2Normalize(playerDirection), speed * frameTime);
    worldPosition = Vector2Add(worldPosition, positionShift);
    
    for (Entity* entity : entities) {
        if (entity == this) { continue; } // Do not collide with self

        if (CheckCollisionRecs(this->GetCollider(), entity->GetCollider())) { 
            worldPosition = oldWorldPosition;
            return; // early exit, cannot move
        }
    }    
}

void Enemy::UpdateAnimationFrame() {
    runningTime += frameTime;
    if (runningTime >= animationFramePeriod) {
        animationFrame++;
        if (animationFrame > 6) {animationFrame = 0; } // End of animation queue

        frameRect.x = animationFrame * entityWidth;
        runningTime = 0.0;
    }
}
