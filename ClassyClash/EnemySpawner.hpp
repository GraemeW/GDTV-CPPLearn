#pragma once
using std::string;
#include <string>
#include <vector>
#include "raylib.h"
#include "Enemy.hpp"
#include "ScoreBoard.hpp"

#ifndef EnemySpawner_h
#define EnemySpawner_h
enum EnemyType {
    GoblinType,
    SlimeType
};

class EnemySpawner
{
private:
    // Random Spawn Properties
    int enemyTypeCount{2}; // match to Enum, no way to do this automatically in C++
    Vector2 randomRange{400.0, 2400.0};
    float randomSpawnTimer{1.0}; // seconds

    // Tunables:  Enemies
    string goblinTexturePathActive = "characters/goblin_run_spritesheet.png";
    string goblinTexturePathIdle = "characters/goblin_idle_spritesheet.png";
    int goblinxyFrameCount[2] = {6, 1};
    float goblinSpeed{200.0};
    float goblinAggroRadiusSq{40000};
    std::vector<Vector2> goblinCoordinates {Vector2{800.0, 800.0}};
    float goblinPadding{0.0};
    float goblinHitPoints{10.0};
    float goblinDamage{5.0};
    float goblinDamageCooldown{0.25};
    int goblinScore{2};

    string slimeTexturePathActive = "characters/slime_run_spritesheet.png";
    string slimeTexturePathIdle = "characters/slime_idle_spritesheet.png";
    int slimexyFrameCount[2] = {6, 1};
    float slimeSpeed{150.0};
    float slimeAggroRadiusSq{80000};
    std::vector<Vector2> slimeCoordinates {Vector2{950.0, 2150.0}};
    float slimePadding{0.0};
    float slimeHitPoints{5.0};
    float slimeDamage{5.0};
    float slimeDamageCooldown{0.10};
    int slimeScore{1};

    // Cached References
    Vector2 gameDimensions{};
    float animationRate{};
    ScoreBoard* scoreBoard;

    // State
    std::vector<Enemy *> enemies;
    float accumulatedTime{0.0};

    // Methods
    void SpawnEnemies(enum EnemyType enemyType, std::vector<Vector2> enemyCoordinates);
    Enemy* SpawnEnemy(enum EnemyType enemyType, Vector2 coordinate, Vector2 gameDimensions, float animationRate);
    Enemy* SpawnRandomEnemy();

public:
    EnemySpawner(Vector2 gameDimensions, float animationRate, ScoreBoard* scoreBoard);
    void SpawnTick(float frameTime);
};
#endif
