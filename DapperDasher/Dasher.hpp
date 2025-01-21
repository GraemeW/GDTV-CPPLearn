//
// Dasher.h
// DapperDasher
//

#pragma once
using std::string;
#include <string>
#include "raylib.h"

#ifndef Dasher_h
#define Dasher_h
class Dasher
{
private:
    // Properties
    const float frameTimeScaler{50.0};
    float jumpForce{15.0}; // Default, overridden by Setter
    float characterMass{1.0}; // Default, overridden by Setter
    float jumpBufferTime{0.15}; // Default, overridden by Setter

    // Cached
    Texture2D texture2D;
    Rectangle frameRect;
    int gameWidth;
    int gameHeight;
    float animationFramePeriod;

    // State
    float yVelocity{0};
    bool isInAir{false};
    float jumpTimer{999.0};
    int animationFrame{0};
    float runningTime{0};

public:
    Dasher(string texturePath, int gameWidth, int gameHeight, float animationFramePeriod);
    ~Dasher();

    // State
    Vector2 dasherPosition;
    int dasherWidth;
    int dasherHeight;

    // Setters & Getters
    void SetAnimationRate(float animationRate);
    void SetAnimationFramePeriod(float animationFramePeriod);
    void SetDasherState();
    bool GetDasherState();
    void SetDasherProperties(float jumpForce, float characterMass, float jumpBufferTime);
    float GetScaledFrameTime(float frameTime);

    void ClampPosition();
    void ClampVelocity();

    void IncrementYVelocity(float velocityAdjustment, float frameTime);
    void IncrementJumpTimer(float frameTime);
    void ApplyJumpForce(float frameTime);
    void UpdatePosition(float frameTime);
    void UpdateAnimationFrame(float frameTime);
    void DrawDasher();
};
#endif
