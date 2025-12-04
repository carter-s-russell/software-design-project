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

        // 2. Settings Button
        if (x >= BTN_X && x <= BTN_X + BTN_WIDTH && 
            y >= BTN_SETTINGS_Y && y <= BTN_SETTINGS_Y + BTN_HEIGHT) {
            while(LCD.Touch(&x, &y));
            return ScreenType::SETTINGS;
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
    // --- 1. Background & Border ---
    LCD.Clear(BLACK);
    
    // Draw a double gold border around the screen
    LCD.SetFontColor(GOLD); //
    LCD.DrawRectangle(5, 5, 310, 230);
    LCD.DrawRectangle(8, 8, 304, 224);

    // --- 2. Title Section ---
    LCD.SetFontColor(WHITE);
    // Use the helper from Screen.h to center the main title
    centerText("CHESS", 15); 
    
    LCD.SetFontColor(GRAY);
    centerText("Proteus Simulator ver.", 35); // Subtitle

    // --- 3. Button Styling Helper ---
    auto drawFancyButton = [&](int y, const char* label) {
        // A. Draw Shadow (Offset by +3 pixels)
        LCD.SetFontColor(DARKGRAY);
        LCD.FillRectangle(BTN_X + 3, y + 3, BTN_WIDTH, BTN_HEIGHT);

        // B. Draw Main Button Body
        LCD.SetFontColor(ROYALBLUE); 
        LCD.FillRectangle(BTN_X, y, BTN_WIDTH, BTN_HEIGHT);

        // C. Draw Button Border
        LCD.SetFontColor(WHITE);
        LCD.DrawRectangle(BTN_X, y, BTN_WIDTH, BTN_HEIGHT);

        // D. Center Text INSIDE the Button
        // (We calculate relative to BTN_WIDTH, not Screen Width)
        int len = 0; 
        while(label[len] != '\0') len++;
        
        int textWidth = len * 12; // Approx width (12px per char)
        int textX = BTN_X + (BTN_WIDTH - textWidth) / 2;
        int textY = y + (BTN_HEIGHT / 2) - 6; // Center vertically (approx)

        LCD.WriteAt(label, textX, textY);
    };

    // --- 4. Draw All Buttons ---
    drawFancyButton(BTN_PLAY_Y, "Play Game");
    drawFancyButton(BTN_SETTINGS_Y, "Settings");
    drawFancyButton(BTN_INSTR_Y, "Instructions");
    drawFancyButton(BTN_CREDITS_Y, "Credits");
    
    // Make the Quit button red to distinguish it
    auto drawQuitButton = [&](int y, const char* label) {
        LCD.SetFontColor(DARKGRAY); // Shadow
        LCD.FillRectangle(BTN_X + 3, y + 3, BTN_WIDTH, BTN_HEIGHT);
        LCD.SetFontColor(FIREBRICK); // Main Body (Red)
        LCD.FillRectangle(BTN_X, y, BTN_WIDTH, BTN_HEIGHT);
        LCD.SetFontColor(WHITE); // Border
        LCD.DrawRectangle(BTN_X, y, BTN_WIDTH, BTN_HEIGHT);
        
        // Simple centering logic repeated
        int len = 0; while(label[len] != '\0') len++;
        int textX = BTN_X + (BTN_WIDTH - (len * 12)) / 2;
        LCD.WriteAt(label, textX, y + (BTN_HEIGHT/2) - 6);
    };

    drawQuitButton(BTN_QUIT_Y, "Quit");
}
