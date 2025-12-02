/**
 * @file
 * @brief Main entry point for the chess game.
 * @author Carter Russell
 * @date 2025-11-18
 */

#include "FEHLCD.h"
#include "FEHUtility.h" 
#include "chess/Board.h" 

#include "screen/Screen.h"
#include "screen/MenuScreen.h"
#include "screen/GameScreen.h"
#include "screen/StatisticsScreen.h"
#include "screen/InstructionsScreen.h"
#include "screen/CreditsScreen.h"
#include <iostream>


int main() {
    std::unique_ptr<Screen> currentScreen = std::make_unique<MenuScreen>();

    while (true) {
        // updates current screen and gets the next screen type
        ScreenType nextScreen = currentScreen->update();

        // switch screen if necesary
        if (nextScreen != ScreenType::NONE) {
            switch (nextScreen) {
                case ScreenType::MENU:
                    currentScreen = std::make_unique<MenuScreen>();
                    break;
                case ScreenType::GAME:
                    currentScreen = std::make_unique<GameScreen>();
                    break;
                case ScreenType::STATISTICS:
                    currentScreen = std::make_unique<StatisticsScreen>();
                    break;
                case ScreenType::INSTRUCTIONS:
                    currentScreen = std::make_unique<InstructionsScreen>();
                    break;
                case ScreenType::CREDITS:
                    currentScreen = std::make_unique<CreditsScreen>();
                    break;
                // other screens here
                case ScreenType::EXIT:
                    return 0;
            }
        } // end screen switching
        
        // draw screen
        currentScreen->draw();
        LCD.Update();
        Sleep(0.01);
    }
    
    return 0;
}
