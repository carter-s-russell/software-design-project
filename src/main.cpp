#include "FEHLCD.h"
#include "FEHUtility.h" 
#include "chess/board.h" 

/**
 * @file
 * @brief Main entry point for the chess game.
 * @author Carter Russell
 * @date 2025-11-17
 */

int main() {
    // Clear the screen to a background color
    LCD.Clear(BLACK);
    
    // Create a board object
    Board myBoard;
    
    // Call a function from your library
    myBoard.draw();

    // Write text from the simulator library
    LCD.SetFontColor(WHITE);
    LCD.WriteLine("Hello Chess!");

    // Update the screen to show changes
    LCD.Update();

    // Wait 3 seconds
    Sleep(3.0);

    return 0;
}
