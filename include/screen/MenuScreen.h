/**
 * @file
 * @brief The menu screen class
 * @author Carter Russell
 * @date 2025-12-02
 */

#ifndef MENUSCREEN_H
#define MENUSCREEN_H

#include "screen/Screen.h"
#include "FEHLCD.h"

class MenuScreen : public Screen {
private:
    // Define button constants for easy adjustments
    const int BTN_WIDTH = 200;
    const int BTN_HEIGHT = 30;
    const int BTN_X = (320 - BTN_WIDTH) / 2; // Center horizontally (60)
    
    // Y-coordinates for the 4 buttons
    const int BTN_PLAY_Y = 60;
    const int BTN_STATS_Y = 100;
    const int BTN_INSTR_Y = 140;
    const int BTN_CREDITS_Y = 180;
public:
    ScreenType update() override {
        int x, y;
        
        // Check if user touched the screen
        if (LCD.Touch(&x, &y)) {
            
            // 1. Play Game Button
            if (x >= BTN_X && x <= BTN_X + BTN_WIDTH && 
                y >= BTN_PLAY_Y && y <= BTN_PLAY_Y + BTN_HEIGHT) {
                while(LCD.Touch(&x, &y)); // Wait for release
                return ScreenType::GAME;
            }

            // 2. Statistics Button
            if (x >= BTN_X && x <= BTN_X + BTN_WIDTH && 
                y >= BTN_STATS_Y && y <= BTN_STATS_Y + BTN_HEIGHT) {
                while(LCD.Touch(&x, &y));
                return ScreenType::STATISTICS;
            }

            // 3. Instructions Button
            if (x >= BTN_X && x <= BTN_X + BTN_WIDTH && 
                y >= BTN_INSTR_Y && y <= BTN_INSTR_Y + BTN_HEIGHT) {
                while(LCD.Touch(&x, &y));
                return ScreenType::INSTRUCTIONS;
            }

            // 4. Credits Button
            if (x >= BTN_X && x <= BTN_X + BTN_WIDTH && 
                y >= BTN_CREDITS_Y && y <= BTN_CREDITS_Y + BTN_HEIGHT) {
                while(LCD.Touch(&x, &y));
                return ScreenType::CREDITS;
            }
        }

        return ScreenType::NONE;
    }

    void draw() override {
        LCD.Clear(BLACK);
        
        // Draw Title
        LCD.SetFontColor(WHITE);
        LCD.WriteAt("CHESS GAME", 100, 20);

        // Helper lambda to draw a button
        auto drawButton = [&](int y, const char* label) {
            LCD.SetFontColor(GRAY);
            LCD.FillRectangle(BTN_X, y, BTN_WIDTH, BTN_HEIGHT);
            LCD.SetFontColor(WHITE);
            // Simple centering logic: X + 10 padding
            LCD.WriteAt(label, BTN_X + 10, y + 7);
        };

        // Draw all 4 buttons
        drawButton(BTN_PLAY_Y, "Play Game");
        drawButton(BTN_STATS_Y, "Statistics");
        drawButton(BTN_INSTR_Y, "Instructions");
        drawButton(BTN_CREDITS_Y, "Credits");
    }
};

#endif // MENUSCREEN_H
