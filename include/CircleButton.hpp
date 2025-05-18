#pragma once
#include "raylib.h"
#include <cmath>
#include "Button.hpp"
#include "Game.hpp"

class CircleButton : public Button {
public:
    Texture2D texture = {0};
    Color color = {0};
    int x = 0, y = 0, radius = 0;

    CircleButton() { }

    CircleButton(Texture2D texture, int x, int y, int radius, Color color) {
        this->texture = texture;
        this->color = color;
        this->x = x;
        this->y = y;
        this->radius = radius;
    }

    bool isHoverOver() {
        return sqrt(pow(Game::mousePos.x - (x + texture.width/2), 2) + pow(Game::mousePos.y - (y + texture.height/2), 2)) <= radius;
    }

    void draw() {
        DrawTexture(texture, x, y, color);

        if(isHoverOver()) {
            DrawCircle(x + texture.width/2, y + texture.height/2, radius, Color{192, 192, 192, 127});
        }
    }
};