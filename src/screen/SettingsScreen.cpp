#include "screen/SettingsScreen.h"
#include "FEHLCD.h"

ScreenType SettingsScreen::update() {
    int x, y;
    if (LCD.Touch(&x, &y)) {
        while (LCD.Touch(&x, &y)) {}
        return ScreenType::MENU;
    }
    return ScreenType::NONE;
}

void SettingsScreen::draw() {
    // sets the background to black
    LCD.Clear(BLACK);
    LCD.SetFontColor(WHITE);
    LCD.WriteAt("Settings go here", 25, 25);
}
