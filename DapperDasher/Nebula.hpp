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
    // Virtual Methods
    void UpdatePosition(float frameTime) override;
    void UpdateAnimationFrame(float frameTime) override;
};
#endif
