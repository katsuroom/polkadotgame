#pragma once
#include "raylib.h"
#include "Game.hpp"

class Player {
public:
    int x, y, radius;
    
    Player() {
        this->x = Game::screenWidth / 2;
        this->y = Game::screenHeight / 2;
        this->radius = Game::playerRadius;
    }

    void update(float dt) {
        this->x = Game::mousePos.x;
        this->y = Game::mousePos.y;
    }

    void draw() {
        DrawCircle(x, y, radius, WHITE);
    }
};