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
        Prop* prop = new Prop(bushTexturePath, bushPadding, gameDimensions, bushCoordinate);
        props.push_back(prop);
    }
    // Logs
    for (Vector2 logCoordinate : logCoordinates) {
        Prop* prop = new Prop(logTexturePath, logPadding, gameDimensions, logCoordinate);
        props.push_back(prop);
    }
    // Rocks
    for (Vector2 rockCoordinate : rockCoordinates) {
        Prop* prop = new Prop(rockTexturePath, rockPadding, gameDimensions, rockCoordinate);
        props.push_back(prop);
    }
    // Signs
    for (Vector2 signCoordinate : signCoordinates) {
        Prop* prop = new Prop(signTexturePath, signPadding, gameDimensions, signCoordinate);
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

        std::vector<Entity *> entities; // Empty vector, props don't move and thus cannot collide
        prop->TickPhysics(frameTime, playerWorldPosition, mapBounds, entities, false);
    }
}

void PropManager::TickAnimation() {
    for (Prop* prop : props) {
        if (prop == nullptr) { continue; }
        prop->TickAnimation();
    }
}

std::vector<Entity *> PropManager::GetProps() { 
    std::vector<Entity *> entities;
    for (Prop* prop : props) {
        if (prop == nullptr) { continue; }
        Entity* entity = prop;
        entities.push_back(entity);
    }

    return entities; 
}
