#pragma once
#include "Game.hpp"
#include "Player.hpp"
#include "raylib.h"
#include <cmath>
#include <array>


class Circle {
public:
    double x, y;
    int radius;
    double vx, vy;
    Color color;

    const static inline std::array<Color, 8> colors = {
        Color{85,98,112,255}, Color{78,205,196,255}, Color{70,205,196,255}, Color{255,107,107,255},
        Color{76,87,100,255}, Color{69,183,175,255}, Color{178,218,89,255}, Color{228,95,95,255}
    };

    Circle(bool startInCenter, Player* player) {
        int min = Game::minRadius;
        int max = Game::maxRadius;

        if(player != nullptr) {
            if(min < player->radius - 35)
                min = player->radius - 35;
            if(max < player->radius + 15)
                max = player->radius + 15;
        }

        this->radius = randInt(min, max);
        this->color = colors[randInt(0, colors.size()-1)];

        if(startInCenter) {
            this->x = randInt(0, Game::screenWidth);
            this->y = randInt(0, Game::screenHeight);
            this->vx = randFloat() - 0.5;
            this->vy = randFloat() - 0.5;
        }
        else {
            float r = randFloat();
            if(r > 0.75) {
                this->x = 1 - this->radius;
                this->y = randInt(0, Game::screenHeight);
                this->vx = randFloat();
                this->vy = randFloat() - 0.5;
            }
            else if(r > 0.5) {
                this->x = Game::screenWidth + this->radius - 1;
                this->y = randInt(0, Game::screenHeight);
                this->vx = -randFloat();
                this->vy = randFloat() - 0.5;
            }
            else if(r > 0.25) {
                this->x = randInt(0, Game::screenHeight);
                this->y = 1 - this->radius;
                this->vx = randFloat() - 0.5;
                this->vy = randFloat();
            }
            else {
                this->x = randInt(0, Game::screenHeight);
                this->y = Game::screenHeight + this->radius - 1;
                this->vx = randFloat() - 0.5;
                this->vy = -randFloat();
            }
        }

        this->vx *= Game::speedScale;
        this->vy *= Game::speedScale;

        if(abs(this->vx) + abs(this->vy) < 1) {
            this->vx = this->vx < 0 ? -1 : 1;
            this->vy = this->vy < 0 ? -1 : 1;
        }
    }

    bool inBounds() {
        if(x + radius < 0) return false;
        if(x - radius > Game::screenWidth) return false;
        if(y + radius < 0) return false;
        if(y - radius > Game::screenHeight) return false;
        return true;
    }

    void update(float dt) {
        int elapsed = dt * 1000;

        this->x += this->vx * elapsed / 15;
        this->y += this->vy * elapsed / 15;
    }

    void draw() {
        DrawCircle(x, y, radius, this->color);
    }
};