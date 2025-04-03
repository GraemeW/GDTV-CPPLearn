//
// Player.cpp
// ClassyClash
//

#include <string>
#include "Player.hpp"

// Methods
Player::Player(string runTexturePath, string idleTexturePath, int xyFrameCount[2], Vector2 gameDimensions, float animationFPS) 
: Entity(runTexturePath, idleTexturePath, xyFrameCount, gameDimensions, animationFPS) {
    playerMover = new PlayerMover();
}

Player::~Player() {
    delete playerMover;
}

void Player::SetDeltaFrameTime(float frameTime) {
    Entity::SetDeltaFrameTime(frameTime);
    playerMover->SetDeltaFrameTime(frameTime);
}

void Player::UpdatePosition() {
    Vector2 positionShift = playerMover->GetPositionShift();
    entityPosition = Vector2Add(entityPosition, positionShift);
}

void Player::UpdateAnimationFrame() {
    runningTime += frameTime;
    if (runningTime >= animationFramePeriod) {
        animationFrame++;
        if (animationFrame > 6) {animationFrame = 0; } // End of animation queue

        frameRect.x = animationFrame * entityWidth;
        runningTime = 0.0;
    }
}

bool Player::IsMoving() { return playerMover->IsMoving(); }
bool Player::IsLookingLeft() { return playerMover->IsLookingLeft(); }
