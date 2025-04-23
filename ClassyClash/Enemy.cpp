//
// Enemy.cpp
// ClassyClash
//

#include <string>
#include "Enemy.hpp"

// Methods
Enemy::Enemy(string runTexturePath, string idleTexturePath, int xyFrameCount[2], float padding, Vector2 gameDimensions, float animationFPS, Vector2 worldPosition, float speed, float aggroRadiusSq, float hitPoints, float damage, float damageCooldown, int score, ScoreBoard* scoreBoard)
: Entity(runTexturePath, idleTexturePath, xyFrameCount, padding, gameDimensions, animationFPS) {
    this->entityType = EntityType::EnemyType;
    this->worldPosition = worldPosition;
    this->speed = speed;
    this->aggroRadiusSq = aggroRadiusSq;
    this->hitPoints = hitPoints;
    this->damage = damage;
    this->damageCooldown = damageCooldown;
    this->score = score;
    this->scoreBoard = scoreBoard;
}

void Enemy::ApplyDamage(float damage) {
    hitPoints -= damage;
    damageCooldownTimer = damageCooldown;
    if (hitPoints <= 0.0) {
        if (scoreBoard != nullptr) {
            scoreBoard->AdjustScore(score);
        }

        isAlive = false;
        KillEnemy();
    }
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
    if (damageCooldownTimer > 0.0) { velocity = Vector2Scale(velocity, -1.0); }
    worldPosition = Vector2Add(worldPosition, Vector2Scale(velocity, frameTime));
    
    if (CheckCollisions(this)) {
        worldPosition = oldWorldPosition;
    }
}

void Enemy::UpdateActions(Entity* player) {
    // Find player, set as target if within range
    float playerDistanceSq = Vector2DistanceSqr(worldPosition, player->GetWorldPosition());
    if (playerDistanceSq <= aggroRadiusSq) {
        currentTarget = player;
    }
    else {
        currentTarget = nullptr;
    }

    // Apply damage if overlapping to player
    if (CheckCollisionRecs(this->GetCollider(), player->GetCollider())) {
        player->ApplyDamage(damage);
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

    if (damageCooldownTimer > 0.0) { spriteColor = RED; }
    else { spriteColor = WHITE; }
}

void Enemy::DrawAccessories() { }
