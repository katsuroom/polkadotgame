#pragma once
#include "raylib.h"
#include "Text.hpp"
#include "Score.hpp"
#include <array>
#include <string>

class Leaderboard {
private:
    const int scoreOffset = 90;     // space between listing number and score
    int totalWidth = 0;             // width of one score entry

    std::string filename = "./save.dat";

    void calculateOffset();

    void writeFile();

    bool readFile();

public:
    int x = 0, y = 0;
    int width = 640, height = 480;

    Text title, subtitle, topScores;

    static inline std::array<Score, 5> highScores = {0};

    Leaderboard();

    // return index of new high score, -1 if not
    int isNewHighScore(int score);

    void saveHighScore(int score, std::string name);

    void update();

    void draw();
};