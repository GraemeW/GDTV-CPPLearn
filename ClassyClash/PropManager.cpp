//
// PropManager.cpp
// ClassyClash
//

#include <string>
#include <iostream>
#include "PropManager.hpp"

PropManager::PropManager(Vector2 gameDimensions) {
    // Bushes
    for (Vector2 bushCoordinate : bushCoordinates) {
        Prop* prop = new Prop(bushTexturePath, gameDimensions, bushCoordinate);
        props.push_back(prop);
    }
}

PropManager::~PropManager() {
    for (Prop* prop : props) {
        if (prop == nullptr) { continue; }
        delete prop;
    }
}

void PropManager::TickPhysics(float frameTime, Vector2 playerWorldPosition, Vector4 mapBounds) {
    for (Prop* prop : props) {
        if (prop == nullptr) { continue; }
        prop->TickPhysics(frameTime, playerWorldPosition, mapBounds, false);
    }
}

void PropManager::TickAnimation() {
    for (Prop* prop : props) {
        if (prop == nullptr) { continue; }
        prop->TickAnimation();
    }
}
