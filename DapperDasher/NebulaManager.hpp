//
// NebulaManager.h
// DapperDasher
//

#pragma once
using std::string;
#include <string>
#include <vector>
#include "raylib.h"
#include "Nebula.hpp"

#ifndef NebulaManager_h
#define NebulaManager_h
class NebulaManager
{
private:
    // Fixed Parameters
    string nebulaTexturePath = "textures/12_nebula_spritesheet.png";
    int nebulaxyFrameCount[2]{8, 8};
    
    // Adjustable Parameters -- Override in setter below
    int maxNebulaCount{8};
    Vector2 nebulaSpawnPeriod{0.5, 2.5};
    float nebulaSpawnPeriodLimiter{1.0};
    float nebulaSpeed{-25.0};
    float nebulaCollisionPadPixels{20};

    // State
    float frameTime{0};
    float nebulaSpawnTimer;
    float nebulaSpawnTimeLimit;
    int totalNebulaCount{0};

    // Cached
    int gameDimensions[2];
    float animationRate;
    std::vector<Nebula *> nebulas;

public:
    NebulaManager(const int gameDimensions[2], float animationRate);
    ~NebulaManager();

    // Methods
    void SetDeltaFrameTime(float frameTime);
    void SetNebulaManagerProperties(int maxNebulaCount, Vector2 nebulaSpawnPeriod, float nebulaSpawnPeriodLimiter, float nebulaSpeed);
    int GetTotalNebulaCount();
    void SpawnNebulas();
    void UpdateNebulaPositions();
    void AnimateAndDrawNebulas();
    bool CheckNebulaCollisions(Rectangle dasherRect);
};
#endif
