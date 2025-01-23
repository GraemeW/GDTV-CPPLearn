//
// Nebula.h
// DapperDasher
//

#pragma once
#include "Entity.hpp"

#ifndef Nebula_h
#define Nebula_h
class Nebula : public Entity
{
using Entity::Entity;

private:
    float xVelocity{-10.0};

public:
    // Methods
    void InitializePosition();
    void SetNebulaSpeed(float xVelocity);
    bool IsNebulaOnScreen();

    // Virtual Methods
    void UpdatePosition(float frameTime) override;
    void UpdateAnimationFrame(float frameTime) override;
};
#endif
