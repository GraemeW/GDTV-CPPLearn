//
// Dasher.h
// DapperDasher
//

#pragma once
#include "Entity.hpp"

#ifndef Dasher_h
#define Dasher_h
class Dasher : public Entity
{
using Entity::Entity;

private:
    // Properties
    float jumpForce{15.0}; // Default, overridden by Setter
    float characterMass{1.0}; // Default, overridden by Setter
    float jumpBufferTime{0.15}; // Default, overridden by Setter

    // State
    float yVelocity{0};
    bool isInAir{false};
    float jumpTimer{999.0};

public:
    // Setters & Getters
    void SetDasherState();
    bool GetDasherState();
    void SetDasherProperties(float jumpForce, float characterMass, float jumpBufferTime);

    // Methods
    void ClampPosition();
    void ClampVelocity();
    void IncrementYVelocity(float velocityAdjustment);
    void IncrementJumpTimer();
    void ApplyJumpForce();

    // Virtual Methods
    void UpdatePosition() override;
    void UpdateAnimationFrame() override;
};
#endif
