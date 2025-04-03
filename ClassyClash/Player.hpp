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

public:
    Player(string runTexturePath, string idleTexturePath, int xyFrameCount[2], Vector2 gameDimensions, float animationFPS);
    ~Player();

    // Virtual Methods
    void SetDeltaFrameTime(float frameTime) override;
    void UpdatePosition() override;
    void UpdateAnimationFrame() override;
    bool IsMoving() override;
    bool IsLookingLeft() override;
    Vector2 GetScreenPosition(Vector2 offsetPoint) override;
};
#endif
