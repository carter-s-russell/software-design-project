#include "screen/MenuScreen.h"
#include "FEHLCD.h"

ScreenType MenuScreen::update() {
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

        // 5. Quit Button
        if (x >= BTN_X && x <= BTN_X + BTN_WIDTH && 
            y >= BTN_QUIT_Y && y <= BTN_QUIT_Y + BTN_HEIGHT) {
            while(LCD.Touch(&x, &y));
            return ScreenType::EXIT;
        }
    }

    return ScreenType::NONE;
}

void MenuScreen::draw() {
    LCD.Clear(BLACK);
    
    // Draw Title
    LCD.SetFontColor(WHITE);
    LCD.WriteAt("CHESS GAME", 100, 10);

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
    drawButton(BTN_QUIT_Y, "Quit");
}
