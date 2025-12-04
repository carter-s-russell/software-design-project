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
        LCD.Clear(BLACK);

        LCD.SetFontColor(YELLOW);
        centerText("=== HOW TO PLAY ===", 20);

        LCD.SetFontColor(WHITE);
        
        centerText("1. Select a piece", 60);
        centerText("to see moves.", 80);

        centerText("2. Click a dot", 110);
        centerText("to move there.", 130);

        centerText("3. Capture enemy", 160);
        centerText("Kings to win!", 180);

        LCD.SetFontColor(GRAY);
        centerText("(Click to Return)", 215);    }
};

#endif // INSTRUCTIONSSCREEN_H
