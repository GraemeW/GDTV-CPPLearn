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

void Player::AddWeapon(string weaponTexture, string weaponActiveTexture) {
    weaponTexture2D = LoadTexture(weaponTexture.c_str());
    weaponActiveTexture2D = LoadTexture(weaponActiveTexture.c_str());
    weaponFrameRect.width = weaponTexture2D.width;
    weaponFrameRect.height = weaponTexture2D.height;
    weaponFrameRect.x = 0;
    weaponFrameRect.y = 0;
    hasWeapon = true;
}

Vector2 Player::GetWeaponPosition() {
    Vector2 weaponPosition{this->GetWorldPosition()};
    float xOffset = 2 * entityWidth / 3;
    if (this->IsLookingLeft()) { xOffset *= -1; }

    weaponPosition.x += xOffset;
    return weaponPosition;
}

Vector2 Player::GetWeaponScreenPosition() {
        Vector2 screenCenter = Vector2{gameDimensions.x/2,gameDimensions.y/2};
    
        Vector2 offset = Vector2Subtract(GetWeaponPosition(), this->GetWorldPosition());
        return Vector2Add(screenCenter, offset);
}

void Player::DrawAccessories() {
    if (hasWeapon) {
        // Flipping
        Rectangle weaponFrameRectLook{weaponFrameRect};
        if (this->IsLookingLeft()) { weaponFrameRectLook.width *= -1; }

        // Scaling + Offsetting
        Vector2 weaponScreenPosition = GetWeaponScreenPosition();

        Rectangle scaledFrameRect{
            weaponScreenPosition.x, 
            weaponScreenPosition.y, 
            weaponFrameRect.width * spriteScaler, 
            weaponFrameRect.height * spriteScaler
        };

        // Origin Definition
        Vector2 weaponOrigin{0.0, weaponFrameRect.height};

        DrawTexturePro(weaponTexture2D, weaponFrameRectLook, scaledFrameRect, weaponOrigin, 0.0, WHITE);
    }
}
