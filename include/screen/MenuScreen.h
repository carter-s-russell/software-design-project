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
    const int BTN_PLAY_Y = 40;
    const int BTN_SETTINGS_Y = 80;
    const int BTN_INSTR_Y = 120;
    const int BTN_CREDITS_Y = 160;
    const int BTN_QUIT_Y = 200;
public:
    virtual ScreenType update() override;
    virtual void draw() override;
};

#endif // MENUSCREEN_H
