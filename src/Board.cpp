#include "chess/Board.h"
#include "FEHLCD.h" 
#include "LCDColors.h" 
#include <iostream>
#include <cctype>

// include all chess pieces
#include "chess/Pawn.h"
#include "chess/King.h"
#include "chess/Knight.h"
#include "chess/Bishop.h"
#include "chess/Rook.h"
#include "chess/Queen.h"

const int BOARD_X_OFFSET = 0;
const int BOARD_Y_OFFSET = 0;
const unsigned int LIGHT_SQUARE_COLOR = SEASHELL;
const unsigned int DARK_SQUARE_COLOR = LIGHTSLATEGRAY;

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
                case 'r': newPiece = std::make_unique<Rook>(color); break;
                case 'n': newPiece = std::make_unique<Knight>(color); break;
                case 'b': newPiece = std::make_unique<Bishop>(color); break;
                case 'q': newPiece = std::make_unique<Queen>(color); break;
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
    PieceColor pieceColor = movingPiece->getColor();
    char pieceType = movingPiece->getType();

    // basic piece moving logic
    m_grid[toY][toX] = std::move(m_grid[curY][curX]);

    // advanced logic
    movingPiece->setHasMoved();

    // pawn special move logic
    if (pieceType == 'p') {
        // promotion logic
        int promotionRank = (pieceColor == PieceColor::LIGHT) ? 0 : 7;
        if (toY == promotionRank) {
            drawPromotionSelection(toX, pieceColor);
        }

        // en passant logic
        int enPassantRank = (pieceColor == PieceColor::LIGHT) ? 3 : 4;
        if (curY == enPassantRank && canEnPassant(toX, pieceColor)) {
            std::cout << "removing: " << toX << "," << enPassantRank << std::endl; 
            m_grid[enPassantRank][toX].reset();
        }

    } else if (pieceType == 'k') {
        if (toX-curX == 2) {
            // short castle
            // move rook
            m_grid[curY][5] = std::move(m_grid[curY][7]);
        } else if (toX-curX == -2) {
            // long castle
            // move rook
            m_grid[curY][3] = std::move(m_grid[curY][0]);
        }
    }

    // update en passant status
    if (pieceType == 'p' && std::abs(toY-curY) == 2) {
        setEnPassant(toX, pieceColor);
    } else {
        // -1 does not correlate with any index on the board, so it will never return true for canEnPassant
        setEnPassant(-1, pieceColor);
    }

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
                return true;
            }
        }
    }

    // base case
    return false;
}

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

void Board::drawPromotionSelection(int file, PieceColor color) {
    // lambda function for integer to pixel calculations
    auto getPixelY = [&](int r) { return BOARD_Y_OFFSET + (r * SQUARE_SIZE); };

    int pixelX = BOARD_X_OFFSET + (file * SQUARE_SIZE);

    // starting rank and direction of drawing
    int rank = (color == PieceColor::LIGHT) ? 0 : 7;
    int step = (color == PieceColor::LIGHT) ? 1 : -1;

    // draw four squares of white squares
    int squareY = (color == PieceColor::LIGHT) ? getPixelY(0) : getPixelY(4);
    LCD.SetFontColor(WHITE);
    LCD.FillRectangle(pixelX, squareY, SQUARE_SIZE, SQUARE_SIZE * 4);

    // draw pieces
    // this logic ensures that the queen is drawn on the promotion square for ease
    for (int i = 0; i < 4; i++) {
        int pixelY = getPixelY(rank);
        std::unique_ptr<Piece> piece;

        switch (i) {
            case 0: piece = std::make_unique<Queen>(color); break;
            case 1: piece = std::make_unique<Rook>(color); break;
            case 2: piece = std::make_unique<Bishop>(color); break;
            case 3: piece = std::make_unique<Knight>(color); break;
        }

        if (piece) {
            piece->draw(pixelX, pixelY);
        }

        // move in the direction determined by step
        rank += step;
    }

    // selection logic
    int inputX, inputY;

    // ignore current click
    while(LCD.Touch(&inputY, &inputX));

    // should pause the program until there is an input
    while (true) {
        // wait for input
        while (!LCD.Touch(&inputX, &inputY));

        bool insideMenu = (inputX >= pixelX) && 
                          (inputX < pixelX + SQUARE_SIZE) && 
                          (inputY >= squareY) && 
                          (inputY < squareY + (SQUARE_SIZE * 4));

        if (insideMenu) {
            break; 
        }

        // if the click was invalid, ignore the rest of it
        while(LCD.Touch(&inputX, &inputY));
    }

    // find which square user clicked on
    int selectionIndex = (inputY - squareY) / SQUARE_SIZE;

    // get piece
    std::unique_ptr<Piece> promotionPiece;

    // set piece
    if (color == PieceColor::LIGHT) {
        switch (selectionIndex) {
            case 0: promotionPiece = std::make_unique<Queen>(color); break;
            case 1: promotionPiece = std::make_unique<Rook>(color); break;
            case 2: promotionPiece = std::make_unique<Bishop>(color); break;
            case 3: promotionPiece = std::make_unique<Knight>(color); break;
        }
    } else {
        switch (selectionIndex) {
            case 0: promotionPiece = std::make_unique<Knight>(color); break;
            case 1: promotionPiece = std::make_unique<Bishop>(color); break;
            case 2: promotionPiece = std::make_unique<Rook>(color); break;
            case 3: promotionPiece = std::make_unique<Queen>(color); break;
        }
    }

    // replace pawn with promoted piece
    rank = (color == PieceColor::LIGHT) ? 0 : 7;
    m_grid[rank][file] = std::move(promotionPiece);
}
