//
// Nebula.cpp
// DapperDasher
//

#include <string>
#include "Nebula.hpp"

void Nebula::UpdatePosition(float frameTime)
{
    entityPosition.x += xVelocity * GetScaledFrameTime(frameTime);
}

void Nebula::UpdateAnimationFrame(float frameTime)
{
    runningTime += frameTime;
    if (runningTime >= animationFramePeriod) {
        animationFrame++;

        if (animationFrame > 61) {animationFrame = 0; } // End of animation queue

        int xIndex = animationFrame % 8;
        int yIndex = animationFrame / 8;
        frameRect.x = xIndex * entityWidth;
        frameRect.y = yIndex * entityHeight;
        runningTime = 0.0;
    }
}
