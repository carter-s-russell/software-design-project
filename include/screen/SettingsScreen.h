/**
 * @file
 * @brief The statistics screen class
 * @author Carter Russell
 * @date 2025-12-02
 */

#ifndef SETTINGSSCREEN_H
#define SETTINGSSCREEN_H

#include "screen/Screen.h"
#include "FEHLCD.h"
#include "LCDColors.h"
#include <vector>
#include <string>

extern double g_selectedTime;

class SettingsScreen : public Screen {
private:
    // Available time controls (in minutes)
    std::vector<int> m_timeOptions = {1, 3, 5, 10, 30, 60};
    int m_currentIndex = 2; // Default to index 2 (5 minutes)

    // Button Geometry
    const int ARROW_Y = 100;
    const int LEFT_ARROW_X = 60;
    const int RIGHT_ARROW_X = 220;
    const int ARROW_SIZE = 40;
    
    const int BACK_BTN_Y = 200;
public:
    virtual ScreenType update() override;
    virtual void draw() override;
};

#endif // SETTINGSSCREEN_H
