//
// Nebula.cpp
// DapperDasher
//

#include <string>
#include "Nebula.hpp"

void Nebula::SetNebulaSpeed(float xVelocity) { this->xVelocity = xVelocity; }
bool Nebula::IsNebulaOnScreen() { return entityPosition.x + entityWidth > 0; }

void Nebula::InitializePosition() {
    int yPosition = (gameHeight / 3) + ((double) std::rand() / (RAND_MAX)) * ((2 * gameHeight / 3) - entityHeight);
    int newPosition[2]{gameWidth, yPosition};
    this->OverridePosition(newPosition);
}

void Nebula::UpdatePosition(float frameTime) {
    entityPosition.x += xVelocity * GetScaledFrameTime(frameTime);
}

void Nebula::UpdateAnimationFrame(float frameTime)
{
    runningTime += frameTime;
    if (runningTime >= animationFramePeriod) {
        animationFrame++;

        if (animationFrame > 60) {animationFrame = 0; } // End of animation queue

        int xIndex = animationFrame % 8;
        int yIndex = animationFrame / 8;
        frameRect.x = xIndex * entityWidth;
        frameRect.y = yIndex * entityHeight;
        runningTime = 0.0;
    }
}
