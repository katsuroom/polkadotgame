#include "raylib.h"
#include "Assets.hpp"
#include "Game.hpp"
#include <stdio.h>

int main(void) {

    SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_WINDOW_RESIZABLE);

    InitWindow(Game::screenWidth, Game::screenHeight, "Polka Dot Game");
    SetTargetFPS(60);
    SetExitKey(KEY_NULL);

    Assets::load();
    Game::init();

    while(!WindowShouldClose()) {

        float dt = GetFrameTime();

        Game::update(dt);

        BeginDrawing();
        Game::draw();
        EndDrawing();
    }

    CloseWindow();

    return 0;
}