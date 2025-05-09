#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "raylib.h"
#include "raymath.h"
#include "WorldMap.hpp"
#include "Entity.hpp"
#include "PropSpawner.hpp"
#include "EnemySpawner.hpp"
#include "Player.hpp"
#include "ScoreBoard.hpp"

// ***Tunables***
// Window + Game Settings
Vector2 gameDimensions{384, 384};
const std::string gameTitle{"Classy Clash"};
const Color backgroundColor{WHITE};

const int targetFPS{60};
float animationRate{12.0}; // fps

// Textures & Positions
// Player
float playerHitpoints{20.0};
string knightTexturePathActive = "characters/knight_run_spritesheet.png";
string knightTexturePathIdle = "characters/knight_idle_spritesheet.png";
int knightxyFrameCount[2] = {6, 1};
float knightPadding{0.0};
Vector2 startingPosition{350.0, 350.0};
string weaponTexturePath = "characters/weapon_sword.png";
string WeaponTexturePathActive = "characters/weapon_sword_1.png";
