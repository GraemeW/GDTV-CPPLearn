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

void Enemy::Tick(Entity* player) { 
    float playerDistanceSq = Vector2DistanceSqr(worldPosition, player->GetWorldPosition());
    if (playerDistanceSq <= aggroRadiusSq) {
        currentTarget = player;
    }
    else {
        currentTarget = nullptr;
    }
}

void Enemy::ApplyDamage(float damage) {
    KillEnemy();
}

void Enemy::KillEnemy() {
    Entity::RemoveFromEntities(this);
    delete this;
}

void Enemy::UpdatePosition() {
    if (currentTarget == nullptr) { velocity = Vector2{}; return; } // No target, no need to move

    Vector2 oldWorldPosition = Vector2(worldPosition);
    Vector2 playerDirection = Vector2Subtract(currentTarget->GetWorldPosition(), worldPosition);

    velocity = Vector2Scale(Vector2Normalize(playerDirection), speed);
    worldPosition = Vector2Add(worldPosition, Vector2Scale(velocity, frameTime));
    
    if (CheckCollisions(this)) {
        worldPosition = oldWorldPosition;
    }
}

void Enemy::UpdateActions() { }

void Enemy::UpdateAnimationFrame() {
    runningTime += frameTime;
    if (runningTime >= animationFramePeriod) {
        animationFrame++;
        if (animationFrame > 6) {animationFrame = 0; } // End of animation queue

        frameRect.x = animationFrame * entityWidth;
        runningTime = 0.0;
    }
}

void Enemy::DrawAccessories() { }
