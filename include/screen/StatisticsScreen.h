/**
 * @file
 * @brief The statistics screen class
 * @author Carter Russell
 * @date 2025-12-02
 */

#ifndef STATISTICSSCREEN_H
#define STATISTICSSCREEN_H

#include "screen/Screen.h"
#include "FEHLCD.h"

class StatisticsScreen : public Screen {
public:
    ScreenType update() override {
        int x, y;
        if (LCD.Touch(&x, &y)) {
            return ScreenType::MENU;
        }
        return ScreenType::NONE;
    }

    void draw() override {
        // sets the background to black
        LCD.Clear(BLACK);
        LCD.SetFontColor(WHITE);
        LCD.WriteAt("Statistics go here", 100, 25);
    }
};

#endif // STATISTICSSCREEN_H
