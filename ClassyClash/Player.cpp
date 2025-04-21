//
// Player.cpp
// ClassyClash
//

#include <string>
#include "Player.hpp"

// Methods
Player::Player(string runTexturePath, string idleTexturePath, int xyFrameCount[2], float padding, Vector2 gameDimensions, float animationFPS) 
: Entity(runTexturePath, idleTexturePath, xyFrameCount, padding, gameDimensions, animationFPS) {
    playerController = new PlayerController();
}

Player::~Player() {
    delete playerController;
}

void Player::Tick(Entity* player) { }

void Player::ApplyDamage(float damage) {

}

void Player::UpdatePosition() {
    Vector2 oldWorldPosition = Vector2(worldPosition);

    velocity = playerController->GetVelocity();
    worldPosition = Vector2Add(worldPosition, Vector2Scale(velocity, frameTime));

    if (CheckCollisions(this->GetCollider())) {
        worldPosition = oldWorldPosition;
    }
}

void Player::UpdateActions() {
    if (!hasWeapon) { return; }
    
    if (!attackInCooldown && playerController->IsAttacking()) {
        attackInCooldown = true;

        for (Entity* collidingEntity : FindCollidingEntities(GetWeaponCollider())) {
            collidingEntity->ApplyDamage(10.0);
        }
    }
}

void Player::UpdateAnimationFrame() {
    runningTime += frameTime;
    if (runningTime >= animationFramePeriod) {
        animationFrame++;
        if (animationFrame > 6) {animationFrame = 0; } // End of animation queue
        if (hasWeapon) { UpdateWeaponRotation(); }

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
    float xOffset = 0.65 * entityWidth;
    if (this->IsLookingLeft()) { xOffset *= 0.5; }
    float yOffset = 0.8 * entityWidth;

    weaponPosition.x += xOffset;
    weaponPosition.y += yOffset;
    return weaponPosition;
}

void Player::UpdateWeaponRotation() {
    if (!attackInCooldown) { return; }

    if (attackRotation > weaponMaxRotation) { attackInCooldown = false; attackRotation = 0.0; }
    attackRotation += weaponRotationPerFrame;
}

Vector2 Player::GetWeaponScreenPosition() {
        Vector2 screenCenter = Vector2{gameDimensions.x/2,gameDimensions.y/2};
    
        Vector2 offset = Vector2Subtract(GetWeaponPosition(), this->GetWorldPosition());
        return Vector2Add(screenCenter, offset);
}

Rectangle Player::GetWeaponCollider() {
    Vector2 weaponPosition = GetWeaponPosition();
    Rectangle positionalRect {
        weaponPosition.x,
        weaponPosition.y - weaponFrameRect.height * spriteScaler,
        weaponFrameRect.width  * spriteScaler,
        weaponFrameRect.height  * spriteScaler
    };
    if (IsLookingLeft()) { positionalRect.x -= weaponFrameRect.width * spriteScaler; }
    return positionalRect;
}

void Player::DrawAccessories() {
    if (hasWeapon) {
        bool isLookingLeft{IsLookingLeft()};

        // Flipping
        Rectangle weaponFrameRectLook{weaponFrameRect};
        if (isLookingLeft) { weaponFrameRectLook.width *= -1; }

        // Rotation
        float rotation{attackRotation};
        if (isLookingLeft) { rotation *= -1; }

        // Scaling + Offsetting
        Vector2 weaponScreenPosition = GetWeaponScreenPosition();
        Rectangle scaledFrameRect{
            weaponScreenPosition.x, 
            weaponScreenPosition.y, 
            weaponFrameRect.width * spriteScaler, 
            weaponFrameRect.height * spriteScaler
        };

        // Origin Definition
        Vector2 weaponOrigin{0.0, weaponFrameRect.height * spriteScaler};
        if (isLookingLeft) { weaponOrigin.x = weaponFrameRect.width * spriteScaler; }

        DrawTexturePro(weaponTexture2D, weaponFrameRectLook, scaledFrameRect, weaponOrigin, rotation, WHITE);
    }
}
