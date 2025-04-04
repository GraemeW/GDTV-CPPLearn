//
// WorldMap.cpp
// ClassyClash
//

#include <string>
#include "WorldMap.hpp"

WorldMap::WorldMap() {
    texture2D = LoadTexture(worldMapPath.c_str());
    mapBounds.x = boundOffsets.x * mapScaler;
    mapBounds.y = (texture2D.height - boundOffsets.y) * mapScaler;
    mapBounds.z = boundOffsets.z * mapScaler;
    mapBounds.w = (texture2D.width - boundOffsets.w) * mapScaler;
}

void WorldMap::DrawWorldMap(Vector2 mapPosition) {
    this->mapPosition = mapPosition;
    DrawTextureEx(texture2D, mapPosition, 0.0, mapScaler, WHITE);
}

void WorldMap::DrawWorldMapShift(Vector2 shiftAmount)
{
    Vector2 newMapPosition = Vector2Add(this->mapPosition, shiftAmount);
    DrawWorldMap(newMapPosition);
}

Vector4 WorldMap::GetMapBounds() { return mapBounds; }
