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

void Player::Tick(Entity* player) { }

void Player::UpdatePosition() {
    Vector2 oldWorldPosition = Vector2(worldPosition);

    velocity = playerMover->GetVelocity();
    worldPosition = Vector2Add(worldPosition, Vector2Scale(velocity, frameTime));

    if (CheckCollisions()) {
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
