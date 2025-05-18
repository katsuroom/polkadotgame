#pragma once
#include <random>
#include <stdio.h>

class Game {
public:

    static inline int screenWidth = 800;
    static inline int screenHeight = 600;

    const static inline float circleCount = 1.75;
    const static inline int minRadius = 5;
    const static inline int maxRadius = 55;
    const static inline int speedScale = 3;

    const static inline int playerRadius = 10;

    static inline Vector2 mousePos = {0, 0};

    static void init();
    static void update(float dt);
    static void draw();

    static void start();
    static void death();

    static int maxCircles() {
        return (double)screenWidth * screenHeight / (10 * 1000) / circleCount;
    }
};

// [min, max]
int randInt(int min, int max);

// [0, 1]
float randFloat();