#include "raylib.h"
#include <string>

int main(int argc, char const *argv[])
{
    // Tunables
    int gameWidth = 800;
    int gameHeight = 600;
    std::string gameTitle = "Axe Game";

    // Misc Game Input
    float rootBeer = 1.99;
    double cheeseBurger = 5.99;
    bool shouldHaveLunch = true;

    // Execution
    InitWindow(gameWidth, gameHeight, gameTitle.c_str());

    return 0;
}

