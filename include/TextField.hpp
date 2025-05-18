#pragma once
#include "raylib.h"
#include "Text.hpp"
#include "Assets.hpp"
#include "Game.hpp"
#include "TextButton.hpp"
#include <string>

class TextField {
private:
    Text text;
    Text fullText;
    std::string full;
    const int limit = 3;

    const int buttonOffset = 15;

public:
    TextButton submit;
    std::string input;

    TextField() {
        text = Text(Assets::helvetica, "Enter Your Initials: ", 24);

        full = std::string(text.text) + std::string("______");
        fullText = Text(Assets::helvetica, full.c_str(), 24);

        submit = TextButton(Assets::helvetica, "Submit", 22);
    }

    void update() {

        int key = GetKeyPressed();
        if(key == KEY_NULL) return;

        if(input.length() < limit && key >= KEY_A && key <= KEY_Z) {
            input.push_back((char)key);
        }
        else if(key == KEY_BACKSPACE && input.length() > 0) {
            input.pop_back();
        }
    }

    void draw() {

        int totalWidth = fullText.width + buttonOffset + submit.width;
        submit.x = (Game::screenWidth - totalWidth) / 2 + fullText.width + buttonOffset;
        submit.y = (Game::screenHeight - submit.height) / 2 + 40;

        float x = (Game::screenWidth - totalWidth) / 2;
        float y = (Game::screenHeight - fullText.height) / 2 + 40;

        fullText.draw(x+1, y+1, Color{85, 98, 112, 255});
        fullText.draw(x, y, WHITE);

        DrawTextEx(Assets::helvetica, input.c_str(), Vector2{x + text.width + 5 + 1, y-5+1}, 24, 0, Color{85, 98, 112, 255});
        DrawTextEx(Assets::helvetica, input.c_str(), Vector2{x + text.width + 5, y-5}, 24, 0, WHITE);

        submit.draw();
    }
};