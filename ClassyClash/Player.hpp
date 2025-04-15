//
// Player.h
// ClassyClash
//

#pragma once
#include "Entity.hpp"
#include "PlayerMover.hpp"

#ifndef Player_h
#define Player_h
class Player : public Entity
{
private:
    // Cached References
    PlayerMover* playerMover;

protected:
    // Virtual Methods
    void SetDependentFrameTime(float frameTime) override;
    void Tick(Entity* player) override;
    void UpdatePosition(std::vector<Entity *> entities) override;
    void UpdateAnimationFrame() override;
    bool IsMoving() override;
    bool IsLookingLeft() override;

public:
    Player(string runTexturePath, string idleTexturePath, int xyFrameCount[2], float padding, Vector2 gameDimensions, float animationFPS);
    ~Player();
    void TickPhysics(float frameTime, Vector4 mapBounds, std::vector<Entity *> entities, bool isPlayer = false) override;
    void TickAnimation(Entity* player) override;
};
#endif
