//
// PropSpawner.cpp
// ClassyClash
//

#include <string>
#include <iostream>
#include "PropSpawner.hpp"

PropSpawner::PropSpawner(Vector2 gameDimensions) {
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

PropSpawner::~PropSpawner() {
    for (Prop* prop : props) {
        if (prop == nullptr) { continue; }
        delete prop;
    }
}
