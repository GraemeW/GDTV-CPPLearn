//
// Background.cpp
// DapperDasher
//

#include <string>
#include "Background.hpp"

Background::Background(BackgroundType backgroundType, float scrollSpeed, const int gameDimensions[2]) {
    this->scrollSpeed = scrollSpeed;
    this->gameDimensions[0] = gameDimensions[0];
    this->gameDimensions[1] = gameDimensions[1];

    switch(backgroundType) {
        case BackgroundType::BUILDINGS:
            texture2D = LoadTexture(backgroundBuildingsPath.c_str());
            break;
        case BackgroundType::FOREGROUND:
            texture2D = LoadTexture(backgroundForegroundPath.c_str());
            break;
        case BackgroundType::BACKING:
            texture2D = LoadTexture(backgroundBackingPath.c_str());
            break;
    }

    scale = (float)gameDimensions[1] / (float)texture2D.height;
    scrollingForward = scrollSpeed < 0;

    positionA.x = 0;
    positionA.y = 0;
    positionB.x = texture2D.width * scale;
    if (scrollingForward) { positionB.x = -texture2D.width * scale; }
    positionB.y = 0;
}

void Background::SetDeltaFrameTime(float frameTime) { this->frameTime = frameTime; }

void Background::AnimateBackground() {
    positionA.x -= scrollSpeed * frameTime;
    positionB.x -= scrollSpeed * frameTime;

    if (!scrollingForward) {
        if (positionA.x < -texture2D.width * scale) {
            positionA.x = positionB.x;
            positionB.x = positionA.x + texture2D.width * scale;
        }
    }
    else {
        if (positionB.x > 0) {
            positionA.x = positionB.x;
            positionB.x = positionA.x - texture2D.width * scale;
        }
    }
}

void Background::DrawBackground() {
    DrawTextureEx(texture2D, positionA, 0, scale, WHITE);
    DrawTextureEx(texture2D, positionB, 0, scale, WHITE);
}
