//
// Player.cpp
// ClassyClash
//

#include <string>
#include "Player.hpp"

// Methods
Player::Player(string runTexturePath, string idleTexturePath, int xyFrameCount[2], float padding, Vector2 gameDimensions, float animationFPS) 
: Entity(runTexturePath, idleTexturePath, xyFrameCount, padding, gameDimensions, animationFPS) {
    playerMover = new PlayerMover();
}

Player::~Player() {
    delete playerMover;
}

void Player::SetDependentFrameTime(float frameTime) {
    this->frameTime = frameTime;
    playerMover->SetDeltaFrameTime(frameTime);
}

void Player::UpdatePosition(std::vector<Entity *> entities) {
    Vector2 oldWorldPosition = Vector2(worldPosition);

    Vector2 positionShift = playerMover->GetPositionShift();
    worldPosition = Vector2Add(worldPosition, positionShift);

    if (CheckCollisions(entities)) {
        worldPosition = oldWorldPosition;
    }
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
