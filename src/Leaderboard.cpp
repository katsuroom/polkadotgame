#include "Leaderboard.hpp"
#include "Assets.hpp"
#include "Game.hpp"

#include <fstream>

Leaderboard::Leaderboard() {
    title = Text(Assets::font, "Polka Dot Game", 96);
    subtitle = Text(Assets::helvetica, "Eat Smaller Dots, Avoid Bigger Dots", 24);
    topScores = Text(Assets::helvetica, "Top Scores", 24);

    bool res = readFile();

    // initialize default leaderboard values
    if(res == false) {
        for(int i = 0; i < highScores.size(); ++i) {
            highScores[i].score = (5-i)*20;
            highScores[i].name = new std::string("- - -");
        }
    }

    calculateOffset();
}

void Leaderboard::calculateOffset() {
    // use first score entry
    Vector2 dim1 = MeasureTextEx(Assets::helvetica, "1. ", 24, 0);
    std::string scoreText = std::to_string(highScores[0].score);
    Vector2 dim2 = MeasureTextEx(Assets::helvetica, scoreText.c_str(), 24, 0);

    totalWidth = dim1.x + scoreOffset + dim2.x;
}

int Leaderboard::isNewHighScore(int score) {
    for(int i = 0; i < highScores.size(); ++i) {
        if(score > highScores[i].score) {
            return i;
        }
    }
    return -1;
}

void Leaderboard::saveHighScore(int score, std::string name) {

    int index = isNewHighScore(score);

    // free bottom
    delete highScores[highScores.size()-1].name;

    // push all down
    for(int j = highScores.size() - 2; j >= index; --j) {
        highScores[j+1] = highScores[j];
    }

    // rewrite score
    highScores[index].score = score;
    highScores[index].name = new std::string(name);

    calculateOffset();

    writeFile();
}

void Leaderboard::writeFile() {
    std::ofstream file;
    file.open(filename, std::ios::trunc);

    for(int i = 0; i < highScores.size(); ++i) {

        // write name length
        int8_t length = sizeof(highScores[i].name->length());
        file.write((char*)&length, sizeof(int8_t));

        // write name
        const char* name = highScores[i].name->c_str();
        file.write(name, length);

        // write score
        file.write((char*)&highScores[i].score, sizeof(int));
    }

    file.close();
}

bool Leaderboard::readFile() {
    std::ifstream file;
    file.open(filename, std::ios::in);

    if(file.is_open() == false) {
        return false;
    }

    for(int i = 0; i < highScores.size(); ++i) {

        // read from file
        int8_t length;
        file.read((char*)&length, sizeof(int8_t));

        // allocate buffer for name
        char* name = new char[length+1];
        name[length] = 0;
        
        // read name and free buffer
        file.read(name, length);
        highScores[i].name = new std::string(name);
        delete name;

        file.read((char*)&highScores[i].score, sizeof(int));
    }

    return true;
}

void Leaderboard::update() {
    this->x = (Game::screenWidth - width) / 2;
    this->y = (Game::screenHeight - height) / 2;
}

void Leaderboard::draw() {
    DrawRectangle(x, y, width, height, WHITE);

    title.draw(x + (width - title.width)/2, y + 24, Color{85, 98, 112, 255});
    subtitle.draw(x + (width - subtitle.width)/2, y + 144, Color{85, 98, 112, 255});
    topScores.draw(x + (width - topScores.width)/2, y + 200, Color{196, 77, 88, 255});


    float xOffset = x + (width - totalWidth)/2;

    for(int i = 0; i < highScores.size(); ++i) {

        std::string number = std::to_string(i+1) + ". ";

        DrawTextEx(Assets::helvetica, number.c_str(),
            Vector2{xOffset, (float)y + 250 + i*30},
            24, 0, Color{85, 98, 112, 255});

        Vector2 dim = MeasureTextEx(Assets::helvetica, number.c_str(), 24, 0);

        DrawTextEx(Assets::helvetica, highScores[i].name->c_str(),
            Vector2{xOffset + dim.x, (float)y + 250 + i*30},
            24, 0, Color{85, 98, 112, 255});

        DrawTextEx(Assets::helvetica, std::to_string(highScores[i].score).c_str(),
            Vector2{xOffset + dim.x + scoreOffset, (float)y + 250 + i*30},
            24, 0, Color{85, 98, 112, 255});
    }
}