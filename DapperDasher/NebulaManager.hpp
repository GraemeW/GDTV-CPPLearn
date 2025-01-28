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
    Vector2 nebulaSpawnPeriod{0.2, 1.5};
    float nebulaSpawnPeriodLimiter{0.5};
    float nebulaSpeed{-25.0};

    // State
    float nebulaSpawnTimer;
    float nebulaSpawnTimeLimit;

    // Cached
    int gameDimensions[2];
    float animationRate;
    std::vector<Nebula *> nebulas;

public:
    NebulaManager(const int gameDimensions[2], float animationRate);
    ~NebulaManager();

    // Methods
    void SetNebulaManagerProperties(int maxNebulaCount, Vector2 nebulaSpawnPeriod, float nebulaSpawnPeriodLimiter, float nebulaSpeed);
    void SpawnNebulas(float frameTime);
    void UpdateNebulaPositions(float frameTime);
    void AnimateAndDrawNebulas(float frameTime);
};
#endif
