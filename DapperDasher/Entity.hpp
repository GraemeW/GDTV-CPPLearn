//
// Entity.h
// DapperDasher
//

#pragma once
using std::string;
#include <string>
#include "raylib.h"

#ifndef Entity_h
#define Entity_h
class Entity
{
protected:
    // Properties
    const float frameTimeScaler{50.0};

    // Cached
    Texture2D texture2D;
    Rectangle frameRect;
    int gameWidth;
    int gameHeight;
    float animationFramePeriod;

    // State
    int animationFrame{0};

public:
    Entity(string texturePath, int xFrameCount, int yFrameCount, int gameWidth, int gameHeight, float animationFPS);
    ~Entity();

    // State
    Vector2 entityPosition;
    int entityWidth;
    int entityHeight;

    // Setters & Getters
    void SetAnimationRate(float animationRate);
    void SetAnimationFramePeriod(float animationFramePeriod);
    float GetScaledFrameTime(float frameTime);

    // Methods
    virtual void UpdatePosition(float frameTime) = 0;
    virtual void UpdateAnimationFrame(float frameTime) = 0;
    void DrawEntity();

};
#endif