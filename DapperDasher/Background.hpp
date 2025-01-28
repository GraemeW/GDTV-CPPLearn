//
// Background.h
// DapperDasher
//

#pragma once
using std::string;
#include <string>
#include "raylib.h"

#ifndef Background_h
#define Background_h
enum BackgroundType {
    BUILDINGS,
    FOREGROUND,
    BACKING
};

class Background
{
private:
    // Fixed Parameters
    string backgroundBuildingsPath = "textures/back-buildings.png";
    string backgroundForegroundPath = "textures/foreground.png";
    string backgroundBackingPath = "textures/far-buildings.png";

    // Cached
    float scrollSpeed{0};
    bool scrollingForward{false};
    Texture2D texture2D;
    int gameDimensions[2];

    // State
    float scale{0};
    float frameTime{0};
    Vector2 positionA;
    Vector2 positionB;

public:
    Background(BackgroundType backgroundType, float scrollSpeed, const int gameDimensions[2]);
    ~Background() {UnloadTexture(texture2D);};

    // Methods
    void SetDeltaFrameTime(float frameTime);
    void AnimateBackground();
    void DrawBackground();
};
#endif
