//
// Enemy.cpp
// ClassyClash
//

#include <string>
#include "Enemy.hpp"

// Methods
Enemy::Enemy(string runTexturePath, string idleTexturePath, int xyFrameCount[2], float padding, Vector2 gameDimensions, float animationFPS, Vector2 worldPosition, float speed, float aggroRadiusSq)
: Entity(runTexturePath, idleTexturePath, xyFrameCount, padding, gameDimensions, animationFPS) {
    this->worldPosition = worldPosition;
    this->speed = speed;
    this->aggroRadiusSq = aggroRadiusSq;
}

void Enemy::SetDependentFrameTime(float frameTime) { this->frameTime = frameTime; }
bool Enemy::IsMoving() { return isMoving; }
bool Enemy::IsLookingLeft() { return isLookingLeft; }

void Enemy::Tick(Entity* player) { 
    float playerDistanceSq = Vector2DistanceSqr(worldPosition, player->GetWorldPosition());
    if (playerDistanceSq <= aggroRadiusSq) {
        currentTarget = player;
    }
    else {
        currentTarget = nullptr;
    }
}

void Enemy::UpdatePosition() {
    if (currentTarget == nullptr) { return; } // No target, no need to move

    Vector2 oldWorldPosition = Vector2(worldPosition);
    Vector2 playerDirection = Vector2Subtract(currentTarget->GetWorldPosition(), worldPosition);
    isLookingLeft = Vector2DotProduct(playerDirection, Vector2{1.0, 0.0}) < 0.0;

    Vector2 positionShift = Vector2Scale(Vector2Normalize(playerDirection), speed * frameTime);
    worldPosition = Vector2Add(worldPosition, positionShift);
    
    if (CheckCollisions()) {
        worldPosition = oldWorldPosition;
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
