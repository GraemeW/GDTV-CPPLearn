//
// Enemy.h
// ClassyClash
//

#pragma once
#include <string>
#include "Entity.hpp"

#ifndef Enemy_h
#define Enemy_h
class Enemy : public Entity
{
private:
    // State
    float speed{};
    float aggroRadiusSq{};
    Entity* currentTarget{nullptr};

protected:
    // Virtual Methods
    void Tick(Entity* player) override;
    void UpdatePosition() override;
    void UpdateActions() override;
    void UpdateAnimationFrame() override;
    void DrawAccessories() override;

public:
    Enemy(string runTexturePath, string idleTexturePath, int xyFrameCount[2], float padding, Vector2 gameDimensions, float animationFPS, Vector2 worldPosition, float speed, float aggroRadiusSq);
    void ApplyDamage(float damage) override;
    void KillEnemy();
};
#endif
