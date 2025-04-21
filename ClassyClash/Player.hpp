//
// Player.h
// ClassyClash
//

#pragma once
#include "Entity.hpp"
#include "PlayerController.hpp"

#ifndef Player_h
#define Player_h
class Player : public Entity
{
private:
    // Tunables
    float weaponMaxRotation{40.0};
    float weaponRotationPerFrame{20.0};

    // Cached References
    PlayerController* playerController;
    Texture2D weaponTexture2D;
    Texture2D weaponActiveTexture2D;
    Rectangle weaponFrameRect;

    // State
    bool hasWeapon{0};
    bool attackInCooldown{false};
    float attackRotation{0};

    // Methods
    Vector2 GetWeaponPosition();
    void UpdateWeaponRotation();
    Vector2 GetWeaponScreenPosition();
    Rectangle GetWeaponCollider();

protected:
    // Virtual Methods
    void Tick(Entity* player) override;
    void UpdatePosition() override;
    void UpdateActions() override;
    void UpdateAnimationFrame() override;
    void DrawAccessories() override;

public:
    Player(string runTexturePath, string idleTexturePath, int xyFrameCount[2], float padding, Vector2 gameDimensions, float animationFPS);
    ~Player();

    // Other Methods
    void AddWeapon(string weaponTexture, string weaponActiveTexture);
};
#endif
