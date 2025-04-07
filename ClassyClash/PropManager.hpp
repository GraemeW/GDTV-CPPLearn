//
// PropManager.h
// ClassyClash
//

#pragma once
using std::string;
#include <string>
#include <vector>
#include "raylib.h"
#include "Prop.hpp"

#ifndef PropManager_h
#define PropManager_h
class PropManager
{
private:
    // Tunables:  Props
    string bushTexturePath = "nature_tileset/Bush.png";
    std::vector<Vector2> bushCoordinates = {Vector2{600.0, 600.0}, Vector2{800.0, 600.0}, Vector2{1000.0, 1200.0}};
    float bushPadding = 30.0;
    string logTexturePath = "nature_tileset/Log.png";
    string rockTexturePath = "nature_tileset/Rock.png";
    string signTexturePath = "nature_tileset/Sign.png";

    // State
    std::vector<Prop *> props;

public:
    PropManager(Vector2 gameDimensions);
    ~PropManager();
    void TickPhysics(float frameTime, Vector2 playerWorldPosition, Vector4 mapBounds);
    void TickAnimation();
    std::vector<Rectangle> GetColliders();
};
#endif
