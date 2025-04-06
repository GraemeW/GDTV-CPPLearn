//
// WorldMap.cpp
// ClassyClash
//

#include <string>
#include "WorldMap.hpp"

WorldMap::WorldMap(Vector2 gameDimensions) {
    
    texture2D = LoadTexture(worldMapPath.c_str());
    mapBounds.x = boundOffsets.x;
    mapBounds.y = texture2D.height * mapScaler - gameDimensions.y - boundOffsets.y;
    mapBounds.z = boundOffsets.z;
    mapBounds.w = texture2D.width * mapScaler - gameDimensions.x - boundOffsets.w;
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
