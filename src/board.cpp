#include "chess/board.h"
#include "FEHLCD.h" 

Board::Board() {
    // Constructor...
}

void Board::draw() {
    // Draw the board logic will go here
    LCD.WriteAt("Drawing board...", 20, 20);
}
