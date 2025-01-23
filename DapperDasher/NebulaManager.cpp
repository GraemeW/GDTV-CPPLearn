//
// NebulaManager.cpp
// DapperDasher
//

#include <string>
#include <iostream>
#include "NebulaManager.hpp"

NebulaManager::NebulaManager(int gameWidth, int gameHeight, float animationRate) {
    this->gameWidth = gameWidth;
    this->gameHeight = gameHeight;
    this->animationRate = animationRate;

    nebulas.reserve(maxNebulaCount);
}

NebulaManager::~NebulaManager() {
    for (int i = 0; i < maxNebulaCount; i++) {
        if (nebulas[i] == nullptr) { continue; }
        delete nebulas[i];
    }
}

void NebulaManager::SetNebulaManagerProperties(int maxNebulaCount, Vector2 nebulaSpawnPeriod, float nebulaSpawnPeriodLimiter, float nebulaSpeed) {
    this->maxNebulaCount = maxNebulaCount;
    this->nebulaSpawnPeriod = nebulaSpawnPeriod;
    this->nebulaSpawnPeriodLimiter = nebulaSpawnPeriodLimiter;
    this->nebulaSpeed = nebulaSpeed;

    nebulas.reserve(maxNebulaCount);
}

void NebulaManager::SpawnNebulas(float frameTime) {
    nebulaSpawnTimer += frameTime;

    if (nebulaSpawnTimer > nebulaSpawnTimeLimit) {
        for (int i = 0; i < maxNebulaCount; i++) {
            if (nebulas[i] != nullptr) { continue; }

            Nebula* nebula = new Nebula(nebulaTexturePath, nebulaXFrameCount, nebulaYFrameCount, gameWidth, gameHeight, animationRate);
            nebula->InitializePosition();
            nebula->SetNebulaSpeed(nebulaSpeed);
            nebulas[i] = nebula;
            break;
        }

        nebulaSpawnTimer = 0;
        if (nebulaSpawnTimeLimit < nebulaSpawnPeriodLimiter) { nebulaSpawnTimeLimit = nebulaSpawnPeriodLimiter + ((double) std::rand() / (RAND_MAX)) * nebulaSpawnPeriod.y; }
        else { nebulaSpawnTimeLimit = nebulaSpawnPeriod.x + ((double) std::rand() / (RAND_MAX)) * nebulaSpawnPeriod.y; }   
    }
}

void NebulaManager::UpdateNebulaPositions(float frameTime) {
    for (int i = 0; i < maxNebulaCount; i++) {
        if (nebulas[i] == nullptr) { continue; }
        nebulas[i]->UpdatePosition(frameTime);

        if (!nebulas[i]->IsNebulaOnScreen()){
            delete nebulas[i];
            nebulas[i] = nullptr;
        }
    }
}

void NebulaManager::AnimateAndDrawNebulas(float frameTime) {
    for (int i = 0; i < maxNebulaCount; i++) {
        if (nebulas[i] == nullptr) { continue; }
        nebulas[i]->UpdateAnimationFrame(frameTime);
        nebulas[i]->DrawEntity();
    }
}
