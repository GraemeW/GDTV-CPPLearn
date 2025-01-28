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
    virtual ~Entity() {UnloadTexture(texture2D);};

    // Properties
    const float frameTimeScaler{25.0};

    // Cached
    Texture2D texture2D;
    Rectangle frameRect;
    int gameWidth;
    int gameHeight;
    float animationFramePeriod;

    // State
    int animationFrame{0};
    float runningTime{0};

public:
    Entity(string texturePath, int xyFrameCount[2], const int gameDimensions[2], float animationFPS);

    // State
    Vector2 entityPosition;
    int entityWidth;
    int entityHeight;

    // Setters & Getters
    void SetAnimationRate(float animationRate);
    void SetAnimationFramePeriod(float animationFramePeriod);
    float GetScaledFrameTime(float frameTime);

    // Methods
    void OverridePosition(int newPosition[2]);
    virtual void UpdatePosition(float frameTime) = 0;
    virtual void UpdateAnimationFrame(float frameTime) = 0;
    void DrawEntity();

};
#endif
