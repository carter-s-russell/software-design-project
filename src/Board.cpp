#include "chess/Board.h"
#include "FEHLCD.h" 
#include "LCDColors.h" 

// include all chess pieces
#include "chess/Pawn.h"

const int SQUARE_SIZE = 30;
const int BOARD_X_OFFSET = 0;
const int BOARD_Y_OFFSET = 0;
const unsigned int LIGHT_SQUARE_COLOR = WHITE;
const unsigned int DARK_SQUARE_COLOR = SLATEGRAY;

// -- Public Member Functions --

Board::Board() {
    setupBoard();
}

void Board::draw() {
    // Loop through all 64 squares
    for (int y = 0; y < 8; ++y) {
        for (int x = 0; x < 8; ++x) {
            // check if the current square is even or odd
            // 0+0 = even, since top right square is light even is light color
            if ((x+y) % 2 == 0) {
                LCD.SetFontColor(LIGHT_SQUARE_COLOR);
            } else {
                LCD.SetFontColor(DARK_SQUARE_COLOR);
            }

            // calculate top left pixel coordinate for this square
            int pixelX = BOARD_X_OFFSET + (x * SQUARE_SIZE);
            int pixelY = BOARD_Y_OFFSET + (y * SQUARE_SIZE);

            // draw the square
            LCD.FillRectangle(pixelX, pixelY, SQUARE_SIZE, SQUARE_SIZE);
            
            // Get the piece at (x, y)
            Piece* piece = getPieceAt(x, y);

            if (piece != nullptr) {
                piece->draw(pixelX, pixelY); 
            }
        }
    }
}

// -- Private Member Functions --

void Board::setupBoard() {
    // clearing the board
    // .reset() clears a unique_ptr
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            m_grid[y][x].reset();
        }
    }

    // initialize pawns
    for (int x = 0; x < 8; x++) {
        m_grid[6][x] = std::make_unique<Pawn>(PieceColor::LIGHT);
        m_grid[1][x] = std::make_unique<Pawn>(PieceColor::DARK);
    }
}
