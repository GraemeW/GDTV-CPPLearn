//
// WorldMap.h
// ClassyClash
//

#pragma once
using std::string;
#include <string>
#include "raylib.h"

#ifndef WorldMap_h
#define WorldMap_h
class WorldMap
{
private:
    // Fixed Parameters
    string worldMapPath = "nature_tileset/WorldMapNoObjects.png";
    float mapScaler{4.0};

    // Cached
    Texture2D texture2D;

    // State
    Vector2 mapPosition{0,0};

public:
    WorldMap();
    ~WorldMap() {UnloadTexture(texture2D);};

    void DrawWorldMap(Vector2 mapPosition);
};
#endif
