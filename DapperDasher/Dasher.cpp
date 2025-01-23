//
// Dasher.cpp
// DapperDasher
//

#include <string>
#include "Dasher.hpp"

// Setters & Getters
void Dasher::SetDasherState() { isInAir = !(entityPosition.y == (gameHeight - texture2D.height)); }
bool Dasher::GetDasherState() { return isInAir; }
void Dasher::SetDasherProperties(float jumpForce, float characterMass, float jumpBufferTime) {
    this->jumpForce = jumpForce;
    this->characterMass = characterMass;
    this->jumpBufferTime = jumpBufferTime;
}

// Methods
void Dasher::ClampPosition() {
    if (entityPosition.y > (gameHeight - entityHeight)) { entityPosition.y = gameHeight - entityHeight; }
    if (entityPosition.y < 0) { entityPosition.y = 0; }
}

void Dasher::ClampVelocity() {
    if (entityPosition.y >= (gameHeight - entityHeight) && yVelocity > 0) { yVelocity = 0; }
}

void Dasher::IncrementYVelocity(float velocityAdjustment, float frameTime) {
    yVelocity += velocityAdjustment * GetScaledFrameTime(frameTime);
}

void Dasher::IncrementJumpTimer(float frameTime) {
    jumpTimer += frameTime;
}

void Dasher::ApplyJumpForce(float frameTime) {
    if (!isInAir || jumpTimer < jumpBufferTime) {
        if (isInAir) { yVelocity = 0; }
        else { jumpTimer = 0; }

        this->IncrementYVelocity(-(jumpForce / characterMass), frameTime);
    }
}

void Dasher::UpdatePosition(float frameTime) {
    entityPosition.y += yVelocity * GetScaledFrameTime(frameTime);
    this->ClampPosition();
}

void Dasher::UpdateAnimationFrame(float frameTime) {
    runningTime += frameTime;
    if (runningTime >= animationFramePeriod) {
        animationFrame++;
        if (animationFrame > 5) {animationFrame = 0; } // End of animation queue

        if (isInAir) { animationFrame = 3; } // Hold jump animation

        frameRect.x = animationFrame * entityWidth;
        runningTime = 0.0;
    }
}
