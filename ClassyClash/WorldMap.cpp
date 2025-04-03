//
// WorldMap.cpp
// ClassyClash
//

#include <string>
#include "WorldMap.hpp"

WorldMap::WorldMap() {
    texture2D = LoadTexture(worldMapPath.c_str());
}

void WorldMap::DrawWorldMap(Vector2 mapPosition) {
    this->mapPosition = mapPosition;
    DrawTextureEx(texture2D, mapPosition, 0.0, mapScaler, WHITE);
}
