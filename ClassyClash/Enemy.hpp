//
// Enemy.h
// ClassyClash
//

#pragma once
#include <string>
#include "Entity.hpp"
#include "ScoreBoard.hpp"

#ifndef Enemy_h
#define Enemy_h
class Enemy : public Entity
{
private:
    // State
    float damage{};
    float speed{};
    float aggroRadiusSq{};
    int score{};
    Entity* currentTarget{nullptr};

    // Cached References
    ScoreBoard* scoreBoard;

protected:
    // Virtual Methods
    void UpdatePosition() override;
    void UpdateActions(Entity* player) override;
    void UpdateAnimationFrame() override;
    void DrawAccessories() override;

public:
    Enemy(string runTexturePath, string idleTexturePath, int xyFrameCount[2], float padding, Vector2 gameDimensions, float animationFPS, Vector2 worldPosition, float speed, float aggroRadiusSq, float hitPoints, float damage, float damageCooldown, int score, ScoreBoard* scoreBoard);
    void ApplyDamage(float damage) override;
    void KillEnemy();
    int GetScore() { return score; }
};
#endif
