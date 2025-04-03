#pragma once
#include <string>
#include <iostream>
#include "raylib.h"
#include "raymath.h"
#include "WorldMap.hpp"
#include "Player.hpp"

// ***Tunables***
// Window + Game Settings
Vector2 gameDimensions{384, 384};
const std::string gameTitle{"Classy Clash"};
const Color backgroundColor{WHITE};

const int targetFPS{60};
float animationRate{12.0}; // fps

// Position
Vector2 startingPosition{-512, -512};

// Textures
string knightTexturePathActive = "characters/knight_run_spritesheet.png";
string knightTexturePathIdle = "characters/knight_idle_spritesheet.png";
int knightxyFrameCount[2] = {6, 1};
