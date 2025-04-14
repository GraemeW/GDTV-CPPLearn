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
    std::vector<Vector2> bushCoordinates = {Vector2{460.0, 500.0}, Vector2{700.0, 660.0}, Vector2{1350.0, 480.0}, Vector2{1640.0, 300.0}, 
        Vector2{350.0, 1020.0}, Vector2{1800.0, 1000.0}, Vector2{1450.0, 1600.0}, Vector2{2350.0, 1280.0}, Vector2{1850.0, 1420.0}, Vector2{2160.0, 1560.0}, 
        Vector2{1020.0, 2010.0}, Vector2{960.0, 2040.0}, Vector2{1020.0, 2080.0}};
    float bushPadding{30.0};
    string logTexturePath = "nature_tileset/Log.png";
    std::vector<Vector2> logCoordinates = {Vector2{420.0, 800.0}, Vector2{1200.0, 700.0}, Vector2{1500.0, 1840.0}};
    float logPadding{20.0};
    string rockTexturePath = "nature_tileset/Rock.png";
    std::vector<Vector2> rockCoordinates = {Vector2{540.0, 120.0}, Vector2{1000.0, 100.0}, Vector2{380.0, 1700.0}, Vector2{1240.0, 1440.0},
        Vector2{120.0, 2220.0}, Vector2{800.0, 2450.0}, Vector2{920.0, 2550.0}, Vector2{2100.0, 2280.0}, Vector2{2400.0, 2100.0}};
    float rockPadding{15.0};
    string signTexturePath = "nature_tileset/Sign.png";
    std::vector<Vector2> signCoordinates = {Vector2{960.0, 1220.0}, {480.0, 2250.0}};
    float signPadding{10.0};

    // State
    std::vector<Prop *> props;

public:
    PropManager(Vector2 gameDimensions);
    ~PropManager();
    void TickPhysics(float frameTime, Vector2 playerWorldPosition, Vector4 mapBounds);
    void TickAnimation();
    std::vector<Entity *> GetProps();
};
#endif
