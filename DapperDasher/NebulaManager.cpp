//
// NebulaManager.cpp
// DapperDasher
//

#include <string>
#include <iostream>
#include "NebulaManager.hpp"

NebulaManager::NebulaManager(const int gameDimensions[2], float animationRate) {
    this->gameDimensions[0] = gameDimensions[0];
    this->gameDimensions[1] = gameDimensions[1];
    this->animationRate = animationRate;

    nebulas.reserve(maxNebulaCount);
    for (int i = 0; i < maxNebulaCount; i++) {
        nebulas.push_back(nullptr);
    }
}

NebulaManager::~NebulaManager() {
    for (int i = 0; i < maxNebulaCount; i++) {
        if (nebulas[i] == nullptr) { continue; }
        delete nebulas[i];
    }
}

void NebulaManager::SetDeltaFrameTime(float frameTime)
{
    this->frameTime = frameTime;
    for (int i = 0; i < maxNebulaCount; i++) {
        if (nebulas[i] == nullptr) { continue; }
        nebulas[i]->SetDeltaFrameTime(frameTime);
    }
}

void NebulaManager::SetNebulaManagerProperties(int maxNebulaCount, Vector2 nebulaSpawnPeriod, float nebulaSpawnPeriodLimiter, float nebulaSpeed) {
    this->maxNebulaCount = maxNebulaCount;
    this->nebulaSpawnPeriod = nebulaSpawnPeriod;
    this->nebulaSpawnPeriodLimiter = nebulaSpawnPeriodLimiter;
    this->nebulaSpeed = nebulaSpeed;

    nebulas.reserve(maxNebulaCount);
}

int NebulaManager::GetTotalNebulaCount() { return totalNebulaCount; }

void NebulaManager::SpawnNebulas() {
    nebulaSpawnTimer += frameTime;

    if (nebulaSpawnTimer > nebulaSpawnTimeLimit) {
        for (int i = 0; i < maxNebulaCount; i++) {
            if (nebulas[i] != nullptr) { continue; }

            Nebula* nebula = new Nebula(nebulaTexturePath, nebulaxyFrameCount, gameDimensions, animationRate);
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

void NebulaManager::UpdateNebulaPositions() {
    for (int i = 0; i < maxNebulaCount; i++) {
        if (nebulas[i] == nullptr) { continue; }
        nebulas[i]->UpdatePosition();

        if (!nebulas[i]->IsNebulaOnScreen()){
            delete nebulas[i];
            nebulas[i] = nullptr;
            totalNebulaCount++;
        }
    }
}

void NebulaManager::AnimateAndDrawNebulas() {
    for (int i = 0; i < maxNebulaCount; i++) {
        if (nebulas[i] == nullptr) { continue; }
        nebulas[i]->UpdateAnimationFrame();
        nebulas[i]->DrawEntity();
    }
}

bool NebulaManager::CheckNebulaCollisions(Rectangle dasherRect) {
    for (int i = 0; i < maxNebulaCount; i++) {
        if (nebulas[i] == nullptr) { continue; }

        if (CheckCollisionRecs(dasherRect, nebulas[i]->GetPositionalRect(nebulaCollisionPadPixels))) {
            std::cout << "Collision detected!" << std::endl;
            return true;
        }
    }
    return false;
}
