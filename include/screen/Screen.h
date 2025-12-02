/**
 * @fil
 * @brief Defines the abstract base class for all screens
 * @author Carter Russell
 * @date 2025-12-02
 */

#ifndef SCREEN_H
#define SCREEN_H

enum class ScreenType {
    NONE, // Stay on the current screen
    MENU,
    GAME,
    STATISTICS,
    INSTRUCTIONS,
    CREDITS,
    EXIT
};

class Screen {
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
