#pragma once
#include "raylib.h"

class Button {
public:
    virtual bool isHoverOver() = 0;

    bool isClicked() {
        return IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && isHoverOver();
    }

    virtual void draw() = 0;
};