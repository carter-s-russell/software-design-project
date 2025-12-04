/**
 * @fil
 * @brief Defines the abstract base class for all screens
 * @author Carter Russell
 * @date 2025-12-02
 */

#ifndef SCREEN_H
#define SCREEN_H

#include "FEHLCD.h"

enum class ScreenType {
    NONE, // Stay on the current screen
    MENU,
    GAME,
    SETTINGS,
    INSTRUCTIONS,
    CREDITS,
    EXIT
};

class Screen {
protected:
    // Constants for layout
    const int SCREEN_WIDTH = 320;
    const int CHAR_WIDTH = 12; 

    void centerText(const char* text, int y) {
        int len = 0;
        while(text[len] != '\0') len++; // Calculate string length
        
        int textWidth = len * CHAR_WIDTH;
        int x = (SCREEN_WIDTH - textWidth) / 2;
        
        LCD.WriteAt(text, x, y);
    }
public:
    virtual ~Screen() {}

    /**
     * @brief Handles input and logic of the screen
     * @return The ScreenType of the next screen to draw
     * Returns NONE if it should stay on the same screen
     */
    virtual ScreenType update() = 0;

    /**
     * @brief Draws the screen
     */
    virtual void draw() = 0;
};

#endif //SCREEN_H
