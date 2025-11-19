#include "chess/Board.h"
#include "FEHLCD.h" 
#include "LCDColors.h" 

// include all chess pieces
#include "chess/Pawn.h"
#include "chess/King.h"

const int BOARD_X_OFFSET = 0;
const int BOARD_Y_OFFSET = 0;
const unsigned int LIGHT_SQUARE_COLOR = WHITE;
const unsigned int DARK_SQUARE_COLOR = SLATEGRAY;

// -- Public Member Functions --

Board::Board() {
    setupBoard();
}

void Board::move(int curX, int curY, int toX, int toY) {
    // get piece being moved
    Piece* movingPiece = getPieceAt(curX, curY);

    // basic piece moving logic
    m_grid[toY][toX] = std::move(m_grid[curY][curX]);

    // advanced logic
    movingPiece->setHasMoved();
    // future enpassant, castling, promotion logic to go here

    // move light king pos
    if (curX == m_lightKingPosX && curY == m_lightKingPosY) {
        m_lightKingPosX = toX;
        m_lightKingPosY = toY;
    }

    // move dark king pos
    if (curX == m_darkKingPosX && curY == m_darkKingPosY) {
        m_darkKingPosX = toX;
        m_darkKingPosY = toY;
    }
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

bool Board::inCheck(PieceColor currentTurn) {
    // getting opposite king pos
    int oppKingPosX = (currentTurn == PieceColor::LIGHT) ? m_darkKingPosX : m_lightKingPosX;
    int oppKingPosY = (currentTurn == PieceColor::LIGHT) ? m_darkKingPosY : m_lightKingPosY;

    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            // getting Piece at current square
            Piece* piece = m_grid[y][x].get();

            // checking if the square is not nullptr and if it can attack the opposite king
            if (piece && piece->isValidMove(x, y, oppKingPosX, oppKingPosY, this)) { 
                return true;
            }
        }
    }

    // base case
    return false;
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
    
    // initialize kings
    m_grid[7][4] = std::make_unique<King>(PieceColor::LIGHT);
    m_grid[0][3] = std::make_unique<King>(PieceColor::DARK);

}
