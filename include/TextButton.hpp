#pragma once
#include "raylib.h"
#include "Button.hpp"
#include "Game.hpp"
#include "Text.hpp"

class TextButton : public Button {
public:
    Text text;

    int x = 0, y = 0;
    int width, height;

    TextButton() {};

    TextButton(Font font, const char* text, int size) {
        this->text = Text(font, text, size);
        
        this->width = this->text.width + 16*2;
        this->height = this->text.height + 8*2;
    }

    bool isHoverOver() {
        if(Game::mousePos.x < x) return false;
        if(Game::mousePos.x > x + width) return false;
        if(Game::mousePos.y < y) return false;
        if(Game::mousePos.y > y + height) return false;
        return true;
    }

    void draw() {
        DrawRectangle(x, y, width, height, Color{196, 77, 88, 255});
        DrawRectangle(x+2, y+2, width-4, height-4, Color{228, 95, 95, 255});
        
        this->text.draw(x + (width - text.width)/2, y + (height - text.height)/2, WHITE);

        if(isHoverOver()) {
            DrawRectangle(x, y, width, height, Color{255, 255, 255, 127});
        }
    }
};