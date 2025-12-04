/**
 * @file
 * @brief The credits screen class
 * @author Carter Russell
 * @date 2025-12-02
 */

#ifndef CREDITSSCREEN_H
#define CREDITSSCREEN_H

#include "screen/Screen.h"
#include "FEHLCD.h"

class CreditsScreen : public Screen {
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
        centerText("=== CREDITS ===", 20);

        LCD.SetFontColor(WHITE);
        centerText("Created By:", 80);
        
        LCD.SetFontColor(CYAN); 
        centerText("Carter Russell", 110);
        centerText("Oliver Martin", 140);

        LCD.SetFontColor(GRAY);
        centerText("(Click to Return)", 210);
    }
};

#endif // CREDITSSCREEN_H
