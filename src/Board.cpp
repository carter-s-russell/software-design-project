#include "chess/Board.h"
#include "FEHLCD.h" 
#include "LCDColors.h" 
#include <iostream>
#include <cctype>

// include all chess pieces
#include "chess/Pawn.h"
#include "chess/King.h"
#include "chess/Knight.h"

const int BOARD_X_OFFSET = 0;
const int BOARD_Y_OFFSET = 0;
const unsigned int LIGHT_SQUARE_COLOR = WHITE;
const unsigned int DARK_SQUARE_COLOR = SLATEGRAY;

// -- Public Member Functions --

Board::Board() {
    setupBoard("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");
}

void Board::setupBoard(const std::string& fen) {
    // clear board
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            m_grid[y][x].reset();
        }
    }

    // parse fen string
    int x = 0;
    int y = 0; // FEN starts at Rank 8 (index 0)

    for (char c : fen) {
        if (c == ' ') {
            break; // stop after the piece placement section
        } else if (c == '/') {
            y++;   // move to the next rank
            x = 0; // reset x to the start of the rank
        } else if (std::isdigit(c)) {
            // if it is a number, skip that many empty squares
            x += (c - '0'); 
        } else {
            PieceColor color = std::isupper(c) ? PieceColor::LIGHT : PieceColor::DARK;
            char lowerC = std::tolower(c);

            std::unique_ptr<Piece> newPiece;

            switch (lowerC) {
                case 'k': 
                    newPiece = std::make_unique<King>(color);
                    // update king pos
                    if (color == PieceColor::LIGHT) {
                        m_lightKingPosX = x; m_lightKingPosY = y;
                    } else {
                        m_darkKingPosX = x; m_darkKingPosY = y;
                    }
                    break;
                case 'p': newPiece = std::make_unique<Pawn>(color); break;
                // case 'r': newPiece = std::make_unique<Rook>(color); break;
                case 'n': newPiece = std::make_unique<Knight>(color); break;
                // case 'b': newPiece = std::make_unique<Bishop>(color); break;
                // case 'q': newPiece = std::make_unique<Queen>(color); break;
            }

            if (newPiece) {
                m_grid[y][x] = std::move(newPiece);
            }
            x++; // move to next square
        }
    }
}

void Board::move(int curX, int curY, int toX, int toY) {
    // get piece being moved
    Piece* movingPiece = getPieceAt(curX, curY);

    // basic piece moving logic
    m_grid[toY][toX] = std::move(m_grid[curY][curX]);

    // advanced logic
    movingPiece->setHasMoved();
    // future enpassant, castling, promotion logic to go here

    // potentially update king pos
    updateKingPos(curX, curY, toX, toY);
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

void Board::drawAvailableMoves(int curX, int curY) {
    // get pointer to selected piece
    Piece* selectedPiece = m_grid[curY][curX].get();

    // loop through all 64 squares
    for (int y = 0; y < 8; ++y) {
        for (int x = 0; x < 8; ++x) {
            if (selectedPiece->isValidMove(curX, curY, x, y, true, this)) {
                // calculate top left pixel coordinate for this square
                int pixelX = BOARD_X_OFFSET + (x * SQUARE_SIZE);
                int pixelY = BOARD_Y_OFFSET + (y * SQUARE_SIZE);

                // test if there is a piece at the desired square
                if (m_grid[y][x].get()) {
                    m_indicatorCapture.Draw(pixelX,pixelY);
                } else {
                    m_indicatorFreeSpace.Draw(pixelX,pixelY);
                }

            }
        }
    }
}

bool Board::isCheck(PieceColor currentTurn) {
    // getting opposite king pos
    int oppKingPosX = (currentTurn == PieceColor::LIGHT) ? m_darkKingPosX : m_lightKingPosX;
    int oppKingPosY = (currentTurn == PieceColor::LIGHT) ? m_darkKingPosY : m_lightKingPosY;

    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            // getting Piece at current square
            Piece* piece = m_grid[y][x].get();

            // checking if the square is not nullptr and if it can attack the opposite king
            // using the false flag for checkSafety because it does not matter if an attacking piece would cause a check,
            // the move is still invalid
            if (piece && piece->isValidMove(x, y, oppKingPosX, oppKingPosY, false, this)) { 
                // std::cout << "Piece giving check: x=" << x << ", y=" << y << " | to: x=" << oppKingPosX << ", y=" << oppKingPosY << std::endl;
                return true;
            }
        }
    }

    // base case
    return false;
}

void Board::updateKingPos(int curX, int curY, int toX, int toY) {
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

// -- Private Member Functions --

bool Board::avoidsCheck(int curX, int curY, int toX, int toY) {
    // get other team color
    PieceColor oppTurn = (m_grid[curY][curX].get()->getColor() == PieceColor::LIGHT) ? PieceColor::DARK : PieceColor::LIGHT;

    // we know that the move is a valid psuedo-move, so now we just have to
    // temporarily move the piece, check for checks, and move it back
    // first, get the piece at the spot being moved to, so we can replace it
    std::unique_ptr<Piece> capturedPiece = std::move(m_grid[toY][toX]);
    // move the piece using std::move, because capturing may not work with the target square removed
    m_grid[toY][toX] = std::move(m_grid[curY][curX]);
    
    // potentially update king pos
    updateKingPos(curX, curY, toX, toY);

    // check to see if there are any checks present
    // uses the opposite team's color to test for the current team being in check
    bool check = isCheck(oppTurn);
    // std::cout << check << std::endl;

    // move piece back
    m_grid[curY][curX] = std::move(m_grid[toY][toX]);

    // replace potentially captured piece, if it is not a nullptr
    // NOTE: std::move is needed because ownership of capturedPiece needs to be 
    // transfered to the parameter
    if (capturedPiece) {
        setPieceAt(toX, toY, std::move(capturedPiece)); 
    }

    // potentially update king pos
    updateKingPos(toX, toY, curX, curY);

    return !check;
}

