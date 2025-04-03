#pragma once
#include <string>
#include <iostream>
#include "raylib.h"
#include "WorldMap.hpp"

// ***Tunables***
// Window + Game Settings
const int targetFPS{60};
const int gameDimensions[2]{384, 384};
const std::string gameTitle{"Classy Clash"};
const Color backgroundColor{WHITE};

// Position
Vector2 startingPosition{-512, -512};
