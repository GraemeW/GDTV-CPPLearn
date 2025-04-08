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
    // Tunables
    float speed{200.0};
    float aggroRadiusSq{40000};

    // State
    float frameTime{0};
    bool isMoving{false};
    bool isLookingLeft{false};

protected:
    // Virtual Methods
    void SetDependentFrameTime(float frameTime) override;
    void UpdatePosition(std::vector<Entity *> entities) override;
    void UpdateAnimationFrame() override;
    bool IsMoving() override;
    bool IsLookingLeft() override;

public:
    Enemy(string runTexturePath, string idleTexturePath, int xyFrameCount[2], float padding, Vector2 gameDimensions, float animationFPS, Vector2 worldPosition);
};
#endif
