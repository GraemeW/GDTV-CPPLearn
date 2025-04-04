//
// WorldMap.h
// ClassyClash
//

#pragma once
using std::string;
#include <string>
#include "raylib.h"
#include "raymath.h"

#ifndef WorldMap_h
#define WorldMap_h
class WorldMap
{
private:
    // Fixed Parameters
    string worldMapPath = "nature_tileset/WorldMapNoObjects.png";
    float mapScaler{4.0};
    Vector4 boundOffsets{7.0, 100.0, 5.0, 100.0}; // W/S/N/E


    // Cached
    Texture2D texture2D;

    // State
    Vector2 mapPosition{0,0};
    Vector4 mapBounds{}; // W/S/N/E

public:
    WorldMap();
    ~WorldMap() {UnloadTexture(texture2D);};

    void DrawWorldMap(Vector2 mapPosition);
    void DrawWorldMapShift(Vector2 shiftAmount);
    Vector4 GetMapBounds();
};
#endif
