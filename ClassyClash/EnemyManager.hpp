#pragma once
using std::string;
#include <string>
#include <vector>
#include "raylib.h"
#include "Enemy.hpp"

#ifndef EnemyManager_h
#define EnemyManager_h
enum EnemyType {
    Goblin,
    Slime
};

class EnemyManager
{
private:
    // Tunables:  Enemies
    string goblinTexturePathActive = "characters/goblin_idle_spritesheet.png";
    string goblinTexturePathIdle = "characters/goblin_run_spritesheet.png";
    int goblinxyFrameCount[2] = {6, 1};
    float goblinSpeed{200.0};
    float goblinAggroRadiusSq{40000};
    std::vector<Vector2> goblinCoordinates {Vector2{800.0, 800.0}};
    float goblinPadding{0.0};

    string slimeTexturePathActive = "characters/slime_idle_spritesheet.png";
    string slimeTexturePathIdle = "characters/slime_idle_spritesheet.png";
    int slimexyFrameCount[2] = {6, 1};
    float slimeSpeed{150.0};
    float slimeAggroRadiusSq{80000};
    std::vector<Vector2> slimeCoordinates {Vector2{950.0, 2150.0}};
    float slimePadding{0.0};

    // Cached References
    Vector2 gameDimensions{};
    float animationRate{};

    // State
    std::vector<Enemy *> enemies;

    // Methods
    void SpawnEnemies(EnemyType enemyType, std::vector<Vector2> enemyCoordinates);
    Enemy* SpawnEnemy(EnemyType enemyType, Vector2 coordinate, Vector2 gameDimensions, float animationRate);

public:
    EnemyManager(Vector2 gameDimensions, float animationRate);
    ~EnemyManager();
    void TickPhysics(float frameTime, Vector2 playerWorldPosition, Vector4 mapBounds, std::vector<Entity *> entities);
    void TickAnimation();
    std::vector<Entity *> GetEnemies();
};
#endif
