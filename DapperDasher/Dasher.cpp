//
// Dasher.cpp
// DapperDasher
//

#include <string>
#include "Dasher.hpp"

Dasher::Dasher(string texturePath, int gameWidth, int gameHeight, float animationFramePeriod) {
    texture2D = LoadTexture(texturePath.c_str());
    this->gameWidth = gameWidth;
    this->gameHeight = gameHeight;
    
    frameRect.width = texture2D.width/6;
    frameRect.height = texture2D.height;
    frameRect.x = 0;
    frameRect.y = 0;
    
    dasherPosition.x = gameWidth/2 - frameRect.width/2;
    dasherPosition.y = gameHeight - frameRect.height;
    this->dasherWidth = frameRect.width;
    this->dasherHeight = frameRect.height;

    this->animationFramePeriod = animationFramePeriod;
}

Dasher::~Dasher() {
    UnloadTexture(texture2D);
}

// Setters & Getters
void Dasher::SetAnimationRate(float animationRate){ animationFramePeriod = 1.0 / animationRate; }
void Dasher::SetAnimationFramePeriod(float animationFramePeriod){ this->animationFramePeriod = animationFramePeriod; }
void Dasher::SetDasherState() { isInAir = !(dasherPosition.y == (gameHeight - texture2D.height)); }
bool Dasher::GetDasherState() { return isInAir; }
void Dasher::SetDasherProperties(float jumpForce, float characterMass, float jumpBufferTime) {
    this->jumpForce = jumpForce;
    this->characterMass = characterMass;
    this->jumpBufferTime = jumpBufferTime;
}
float Dasher::GetScaledFrameTime(float frameTime) { return (frameTime * frameTimeScaler); }

// Methods
void Dasher::ClampPosition() {
    if (dasherPosition.y > (gameHeight - dasherHeight)) { dasherPosition.y = gameHeight - dasherHeight; }
    if (dasherPosition.y < 0) { dasherPosition.y = 0; }
}

void Dasher::ClampVelocity() {
    if (dasherPosition.y >= (gameHeight - dasherHeight) && yVelocity > 0) { yVelocity = 0; }
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
    dasherPosition.y += yVelocity * GetScaledFrameTime(frameTime);
    this->ClampPosition();
}

void Dasher::UpdateAnimationFrame(float frameTime) {
    runningTime += frameTime;
    if (runningTime >= animationFramePeriod) {
        animationFrame++;
        if (animationFrame > 5) {animationFrame = 0; } // End of animation queue

        if (isInAir) { animationFrame = 3; } // Hold jump animation

        frameRect.x = animationFrame * dasherWidth;
        runningTime = 0.0;
    }
}

void Dasher::DrawDasher() {
    DrawTextureRec(texture2D, frameRect, dasherPosition, WHITE);
}
