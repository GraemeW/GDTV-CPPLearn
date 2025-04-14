//
// EnemyManager.cpp
// ClassyClash
//

#include <string>
#include <iostream>
#include "EnemyManager.hpp"

EnemyManager::EnemyManager(Vector2 gameDimensions, float animationRate) 
: gameDimensions(gameDimensions), animationRate(animationRate) {
    SpawnEnemies(EnemyType::Goblin, goblinCoordinates);
    SpawnEnemies(EnemyType::Slime, slimeCoordinates);
}

EnemyManager::~EnemyManager() {
    for (Enemy* enemy : enemies) {
        if (enemy == nullptr) { continue; }
        delete enemy;
    }
}

void EnemyManager::SpawnEnemies(EnemyType enemyType, std::vector<Vector2> enemyCoordinates) {
    for (Vector2 enemyCoordinate : enemyCoordinates) {
        Enemy* enemy = SpawnEnemy(enemyType, enemyCoordinate, gameDimensions, animationRate);
        if (enemy == nullptr) { break; }
        enemies.push_back(enemy);
    }
}

Enemy* EnemyManager::SpawnEnemy(EnemyType enemyType, Vector2 coordinate, Vector2 gameDimensions, float animationRate) {
    switch(enemyType) {
        case EnemyType::Goblin:
        { 
            Enemy* goblin = new Enemy(goblinTexturePathActive, goblinTexturePathIdle, goblinxyFrameCount, goblinPadding, gameDimensions, animationRate, coordinate, goblinSpeed, goblinAggroRadiusSq);
            return goblin;
        }
        case EnemyType::Slime:
        {
            Enemy* slime = new Enemy(slimeTexturePathActive, slimeTexturePathActive, slimexyFrameCount, slimePadding, gameDimensions, animationRate, coordinate, slimeSpeed, slimeAggroRadiusSq);
            return slime;
        }
    }
    return nullptr;
}

void EnemyManager::TickPhysics(float frameTime, Vector2 playerWorldPosition, Vector4 mapBounds, std::vector<Entity *> entities) {
    for (Enemy* enemy : enemies) {
        if (enemy == nullptr) { continue; }
        enemy->TickPhysics(frameTime, playerWorldPosition, mapBounds, entities, false);
    }
}

void EnemyManager::TickAnimation() {
    for (Enemy* enemy : enemies) {
        if (enemy == nullptr) { continue; }
        enemy->TickAnimation();
    }
}

std::vector<Entity *> EnemyManager::GetEnemies() {
    std::vector<Entity *> entities;
    for (Enemy* prop : enemies) {
        if (prop == nullptr) { continue; }
        Entity* entity = prop;
        entities.push_back(entity);
    }
    return entities; 
}
