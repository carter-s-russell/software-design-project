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

class SettingsScreen : public Screen {
public:
    virtual ScreenType update() override;
    virtual void draw() override;
};

#endif // SETTINGSSCREEN_H
