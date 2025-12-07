#include "screen/SettingsScreen.h"
#include "FEHLCD.h"

ScreenType SettingsScreen::update() {
    int x, y;
    if (LCD.Touch(&x, &y)) {
        while(LCD.Touch(&x, &y)); // Wait for release

        // 1. Check Left Arrow (<)
        if (x >= LEFT_ARROW_X && x <= LEFT_ARROW_X + ARROW_SIZE &&
            y >= ARROW_Y && y <= ARROW_Y + ARROW_SIZE) {
            
            if (m_currentIndex > 0) {
                m_currentIndex--;
            }
        }

        // 2. Check Right Arrow (>)
        else if (x >= RIGHT_ARROW_X && x <= RIGHT_ARROW_X + ARROW_SIZE &&
                 y >= ARROW_Y && y <= ARROW_Y + ARROW_SIZE) {
            
            if (m_currentIndex < (int)m_timeOptions.size() - 1) {
                m_currentIndex++;
            }
        }

        // 3. Check "Back / Save" Button
        else if (y >= BACK_BTN_Y && y <= BACK_BTN_Y + 30) {
            // SAVE THE TIME!
            // Convert minutes to seconds for the game logic
            g_selectedTime = m_timeOptions[m_currentIndex] * 60.0;
            return ScreenType::MENU;
        }
    }
    return ScreenType::NONE;
}

void SettingsScreen::draw() {
    LCD.Clear(BLACK);

    // 1. Title
    LCD.SetFontColor(YELLOW);
    centerText("SETTINGS", 20);

    // 2. Label
    LCD.SetFontColor(WHITE);
    centerText("Time Per Player:", 70);

    // 3. Draw Left Arrow (<)
    // Gray out if at the start of the list
    if (m_currentIndex > 0) LCD.SetFontColor(ORANGE);
    else LCD.SetFontColor(DARKGRAY);
    LCD.FillRectangle(LEFT_ARROW_X, ARROW_Y, ARROW_SIZE, ARROW_SIZE);
    LCD.SetFontColor(BLACK);
    LCD.WriteAt("<", LEFT_ARROW_X + 12, ARROW_Y + 12);

    // 4. Draw Right Arrow (>)
    // Gray out if at the end of the list
    if (m_currentIndex < (int)m_timeOptions.size() - 1) LCD.SetFontColor(ORANGE);
    else LCD.SetFontColor(DARKGRAY);
    LCD.FillRectangle(RIGHT_ARROW_X, ARROW_Y, ARROW_SIZE, ARROW_SIZE);
    LCD.SetFontColor(BLACK);
    LCD.WriteAt(">", RIGHT_ARROW_X + 12, ARROW_Y + 12);

    // 5. Draw Selected Time (Center)
    LCD.SetFontColor(WHITE);
    // We need to format the int to a string manually since WriteAt doesn't do printf style easily
    // Or just print the int.
    int minutes = m_timeOptions[m_currentIndex];
    
    // Centering logic for the number
    int numberX = 160 - (minutes >= 10 ? 12 : 6); 
    LCD.WriteAt(minutes, numberX, ARROW_Y + 12);
    LCD.WriteAt("min", 160 - 18, ARROW_Y + 35);

    // 6. Draw Back Button
    LCD.SetFontColor(GRAY);
    centerText("[ Save & Return ]", BACK_BTN_Y);
}
