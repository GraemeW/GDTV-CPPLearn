//
// EnemySpawner.cpp
// ClassyClash
//

#include <string>
#include <iostream>
#include "EnemySpawner.hpp"

EnemySpawner::EnemySpawner(Vector2 gameDimensions, float animationRate) 
: gameDimensions(gameDimensions), animationRate(animationRate) {
    SpawnEnemies(EnemyType::GoblinType, goblinCoordinates);
    SpawnEnemies(EnemyType::SlimeType, slimeCoordinates);

    // Seed the random number generator
    std::srand(std::time(0)); 
}

void EnemySpawner::SpawnEnemies(enum EnemyType enemyType, std::vector<Vector2> enemyCoordinates) {
    for (Vector2 enemyCoordinate : enemyCoordinates) {
        Enemy* enemy = SpawnEnemy(enemyType, enemyCoordinate, gameDimensions, animationRate);
        if (enemy == nullptr) { continue; }
        enemies.push_back(enemy);
    }
}

Enemy* EnemySpawner::SpawnEnemy(enum EnemyType enemyType, Vector2 coordinate, Vector2 gameDimensions, float animationRate) {
    switch(enemyType) {
        case EnemyType::GoblinType:
        { 
            Enemy* goblin = new Enemy(goblinTexturePathActive, goblinTexturePathIdle, goblinxyFrameCount, goblinPadding, gameDimensions, animationRate, coordinate, goblinSpeed, goblinAggroRadiusSq, goblinHitPoints, goblinDamage);
            if (Entity::DeleteOverlappingEntity(goblin)) { return nullptr; }
            return goblin;
        }
        case EnemyType::SlimeType:
        {
            Enemy* slime = new Enemy(slimeTexturePathActive, slimeTexturePathActive, slimexyFrameCount, slimePadding, gameDimensions, animationRate, coordinate, slimeSpeed, slimeAggroRadiusSq, slimeDamage, slimeHitPoints);
            if (Entity::DeleteOverlappingEntity(slime)) { return nullptr; }
            return slime;
        }
    }
    return nullptr;
}

Enemy* EnemySpawner::SpawnRandomEnemy() {
    float xCoordinate = randomRange.x + (randomRange.y - randomRange.x) * (static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
    float yCoordinate = randomRange.x + (randomRange.y - randomRange.x) * (static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
    Vector2 coordinate{xCoordinate, yCoordinate};

    enum EnemyType enemyType = static_cast<enum EnemyType>(rand() % enemyTypeCount);
    Enemy* enemy = SpawnEnemy(enemyType, coordinate, gameDimensions, animationRate);
    return enemy;
}

void EnemySpawner::SpawnTick(float frameTime) {
    accumulatedTime += frameTime;
    if (accumulatedTime > randomSpawnTimer) {
       Enemy* enemy = SpawnRandomEnemy();
       if (enemy == nullptr) { return; }
       
       enemies.push_back(enemy);
       accumulatedTime = 0.0;
    }
}
