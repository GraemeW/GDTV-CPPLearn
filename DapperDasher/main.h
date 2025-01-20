#pragma once
#include <string>
#include <iostream>
#include "raylib.h"

// ***Tunables***
// Window + Game Settings
const int targetFPS{60};
const int gameWidth{800};
const int gameHeight{600};
const std::string gameTitle{"Dapper Dasher"};
const Color backgroundColor{WHITE};

// Methods
float GetScaledFrameTime();
float ClampYVelocity(float yVelocity, int yPos, int gameHeight, int characterHeight);
int ClampYPosition(int yPos, int gameHeight, int characterHeight);
