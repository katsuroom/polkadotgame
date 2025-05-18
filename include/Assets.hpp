#pragma once
#include "raylib.h"

class Assets {
public:
    static inline Font font = {0};
    static inline Font helvetica = {0};
    static inline Texture2D trophy = {0};

    static void load() {
        trophy = LoadTexture("assets/trophy.png");
        font = LoadFontEx("assets/Sacramento-Regular.ttf", 96, nullptr, 0);
        helvetica = LoadFontEx("assets/Helvetica-Bold.ttf", 64, nullptr, 0);
		
		SetTextureFilter(font.texture, TEXTURE_FILTER_BILINEAR);
		SetTextureFilter(helvetica.texture, TEXTURE_FILTER_BILINEAR);
    }
};