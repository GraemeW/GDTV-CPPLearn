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

    // State
    bool hasWeapon{0};
    Texture2D weaponTexture2D;
    Texture2D weaponActiveTexture2D;
    Rectangle weaponFrameRect;
    float swingWeaponRotation{35.0};

    // Methods
    Vector2 GetWeaponPosition();
    Vector2 GetWeaponScreenPosition();
    Rectangle GetWeaponCollider();

protected:
    // Virtual Methods
    void Tick(Entity* player) override;
    void UpdatePosition() override;
    void UpdateAnimationFrame() override;
    void DrawAccessories() override;

public:
    Player(string runTexturePath, string idleTexturePath, int xyFrameCount[2], float padding, Vector2 gameDimensions, float animationFPS);
    ~Player();

    // Other Methods
    void AddWeapon(string weaponTexture, string weaponActiveTexture);
};
#endif
