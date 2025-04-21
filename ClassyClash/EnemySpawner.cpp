//
// EnemySpawner.cpp
// ClassyClash
//

#include <string>
#include <iostream>
#include "EnemySpawner.hpp"

EnemySpawner::EnemySpawner(Vector2 gameDimensions, float animationRate) 
: gameDimensions(gameDimensions), animationRate(animationRate) {
    SpawnEnemies(EnemyType::Goblin, goblinCoordinates);
    SpawnEnemies(EnemyType::Slime, slimeCoordinates);
}

void EnemySpawner::SpawnEnemies(EnemyType enemyType, std::vector<Vector2> enemyCoordinates) {
    for (Vector2 enemyCoordinate : enemyCoordinates) {
        Enemy* enemy = SpawnEnemy(enemyType, enemyCoordinate, gameDimensions, animationRate);
        if (enemy == nullptr) { break; }
        enemies.push_back(enemy);
    }
}

Enemy* EnemySpawner::SpawnEnemy(EnemyType enemyType, Vector2 coordinate, Vector2 gameDimensions, float animationRate) {
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
