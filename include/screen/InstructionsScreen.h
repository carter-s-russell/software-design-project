/**
 * @file
 * @brief The instructions screen class
 * @author Carter Russell
 * @date 2025-12-02
 */

#ifndef INSTRUCTIONSSCREEN_H
#define INSTRUCTIONSSCREEN_H

#include "screen/Screen.h"
#include "FEHLCD.h"

class InstructionsScreen : public Screen {
public:
    ScreenType update() override {
        int x, y;
        if (LCD.Touch(&x, &y)) {
            while (LCD.Touch(&x, &y)) {}
            return ScreenType::MENU;
        }
        return ScreenType::NONE;
    }

    void draw() override {
        // sets the background to black
        LCD.Clear(BLACK);
        LCD.SetFontColor(WHITE);
        LCD.WriteAt("Instructions go here", 25, 25);
    }
};

#endif // INSTRUCTIONSSCREEN_H
