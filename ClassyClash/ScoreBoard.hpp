//
// ScoreBoard.h
// ClassyClash
//

#pragma once
using std::string;
#include <string>
#include "raylib.h"
#include "Player.hpp"

#ifndef ScoreBoard_h
#define ScoreBoard_h
class ScoreBoard
{
private:
    // Tunables
    std::string gameOverMessageA{"You Lose!"};
    std::string gameOverMessageB{"Be Better."};
    std::string scoreMessage{"Score: "};

    // Cached References
    Player* player;
    Vector2 gameDimensions;

    // State
    int score{0};

public:
    ScoreBoard(int initialScore, Player* player, Vector2 gameDimensions);

    // Methods
    void AdjustScore(int amount);
    int GetScore() { return score; }
    void TickScore();
};
#endif
