#include "FEHLCD.h"
#include "FEHUtility.h" 
#include "chess/Board.h" 

/**
 * @file
 * @brief Main entry point for the chess game.
 * @author Carter Russell
 * @date 2025-11-17
 */

int main() {
    Board chessBoard;

    while (true) {
        // sets the background to black
        LCD.Clear(BLACK);

        // draws the board
        chessBoard.draw();

        // updates screen
        LCD.Update();

        // prevents cpu from running at 100%
        Sleep(0.01);
    }

    return 0;
}
