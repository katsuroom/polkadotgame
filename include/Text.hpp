#pragma once
#include "raylib.h"

class Text {
public:
    const char* text;
    Font font;
    int size;
    int width, height;

    Text() {}

    Text(Font font, const char* text, int size) {
        this->text = text;
        this->font = font;
        this->size = size;

        Vector2 dim = MeasureTextEx(font, text, size, 0);
        this->width = dim.x;
        this->height = dim.y;
    }

    void draw(float x, float y, Color color) {
        DrawTextEx(this->font, this->text, Vector2{x, y}, this->size, 0, color);
    }
};