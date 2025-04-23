//
// ScoreBoard.cpp
// ClassyClash
//

#include <string>
#include "ScoreBoard.hpp"

ScoreBoard::ScoreBoard(int initialScore, Player* player, Vector2 gameDimensions)
: player(player), gameDimensions(gameDimensions) {
    score = initialScore;
}

void ScoreBoard::AdjustScore(int amount) {
    score += amount;
}

void ScoreBoard::TickScore() {
    // Score
    string scoreString{scoreMessage};
    scoreString.append(std::to_string(score));
    DrawText(scoreString.c_str(), 0, 0, 24, GREEN);

    // Game Over Message
    if (player != nullptr) {
        if (!player->IsAlive()) {
            DrawText(gameOverMessageA.c_str(), gameDimensions.x / 5, gameDimensions.y / 2 - 50, 48, RED);
            DrawText(gameOverMessageB.c_str(), gameDimensions.x / 5, gameDimensions.y / 2 + 50, 48, RED);
        }
    }
}
