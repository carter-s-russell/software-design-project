#include "screen/GameScreen.h"
#include "screen/SettingsScreen.h"
#include "FEHLCD.h"
#include "FEHUtility.h"

GameScreen::GameScreen() {
    // setting state variables
    m_currentTurn = PieceColor::LIGHT; //
    m_currentState = GameState::AWAITING_SELECTION;

    // set starting time
    m_lightTime = g_selectedTime;
    m_darkTime = g_selectedTime;
    m_lastTime = TimeNow();
}

ScreenType GameScreen::update() {
    // allow user to go back to menu after a checkmate or stalemate
    PieceColor oppCol = (m_currentTurn == PieceColor::LIGHT) ? PieceColor::DARK : PieceColor::LIGHT;
    bool inCheck = m_board.isCheck(oppCol);
    bool canMove = m_board.anyValidMoves(m_currentTurn);
    if ( (inCheck && !canMove) || (!inCheck && !canMove) || m_lightTime == 0 || m_darkTime == 0){
        int x, y;
        while (LCD.Touch(&x, &y)) {}
        if (LCD.Touch(&x, &y)) {
            while (LCD.Touch(&x, &y)) {}
            return ScreenType::MENU;
        }
    }

    // there is no checkmate or stalemate present, so continue with next move
    // time logic
    double currentTime = TimeNow();
    double dt = currentTime - m_lastTime;
    m_lastTime = currentTime;
    if (m_currentTurn == PieceColor::LIGHT) {
        m_lightTime -= dt;
        if (m_lightTime < 0) m_lightTime = 0; // prevent negative time
    } else {
        m_darkTime -= dt;
        if (m_darkTime < 0) m_darkTime = 0;
    }

    // lambda function for pixel to coordinate
    auto pixelToCoord = [](int pixel) {
        return pixel / SQUARE_SIZE;
    };

    // checking for user input
    int pixelX, pixelY;

    // current state of the touch
    m_isTouchPressed = LCD.Touch(&pixelX, &pixelY);

    // this now only runs on the frame that the touch happened
    if (m_isTouchPressed && !m_wasTouchPressed) {
        int gridX = pixelToCoord(pixelX);
        int gridY = pixelToCoord(pixelY);
        bool validGrid = (gridX >= 0) && (gridX < 8) && (gridY >= 0) && (gridY < 8);

        if ((m_currentState == GameState::AWAITING_SELECTION) && validGrid) {
            // std::cout << "select: " << gridX << "," << gridY << std::endl;
            Piece* selectedPiece = m_board.getPieceAt(gridX, gridY);

            // selects piece if the selected square is a piece of the color of the current turn
            if (selectedPiece != nullptr && selectedPiece->getColor() == m_currentTurn) {
                m_selectedX = gridX;
                m_selectedY = gridY;

                // flip current state
                m_currentState = GameState::PIECE_SELECTED;
            }
        } else if ((m_currentState == GameState::PIECE_SELECTED)) {
            // state must flip no matter what input is given
            m_currentState = GameState::AWAITING_SELECTION;

            // allows for clicking outside of board to reset current move
            if (validGrid) {
                // std::cout << "move to: " << gridX << "," << gridY << std::endl;
                Piece* selectedPiece = m_board.getPieceAt(m_selectedX, m_selectedY);
                bool validMove = selectedPiece->isValidMove(m_selectedX, m_selectedY, gridX, gridY, true, &m_board);
                // std::cout << "Valid move: " << validMove << std::endl;
                if (validMove) {
                    m_board.move(m_selectedX, m_selectedY, gridX, gridY);

                    // flip turn using ternary operator
                    m_currentTurn = (m_currentTurn == PieceColor::LIGHT) ? PieceColor::DARK : PieceColor::LIGHT;
                }
            }
        }
    }

    return ScreenType::NONE;
}

void GameScreen::draw() {
    LCD.Clear(BLACK);
    m_board.draw();

    if (m_currentState == GameState::PIECE_SELECTED) {
        m_board.drawAvailableMoves(m_selectedX, m_selectedY);
    }

    // sidebar (240 - 320)
    const int SIDEBAR_X = 245; // 5 pixels of padding
    
    // separator
    LCD.SetFontColor(GRAY); 
    LCD.DrawLine(240, 0, 240, 239); 

    // lambda function for drawing the timer block
    auto drawPlayerBlock = [&](int y, const char* label, double timeRemaining, bool isTurn) {
        // highlight the active player name
        if (isTurn) {
            LCD.SetFontColor(GREEN); // Active
            LCD.FillRectangle(SIDEBAR_X - 2, y + 2, 70, 45); // Highlight box
            LCD.SetFontColor(BLACK); // Text color on highlight
        } else {
            LCD.SetFontColor(GRAY);  // Inactive
        }
        
        LCD.WriteAt(label, SIDEBAR_X, y + 5);

        // Format Time: MM:SS
        int minutes = (int)timeRemaining / 60;
        int seconds = (int)timeRemaining % 60;
        
        // Manual formatting since FEH WriteAt doesn't do printf formatting easily
        // Drawing: " 5:00" or " 4:32"
        if (isTurn) LCD.SetFontColor(BLACK); 
        else LCD.SetFontColor(WHITE);

        // Adjust X for alignment
        LCD.WriteAt(minutes, SIDEBAR_X, y + 25);
        LCD.WriteAt(":", SIDEBAR_X + 24, y + 25);
        
        // Draw leading zero for seconds if needed
        if (seconds < 10) {
            LCD.WriteAt("0", SIDEBAR_X + 36, y + 25);
            LCD.WriteAt(seconds, SIDEBAR_X + 48, y + 25);
        } else {
            LCD.WriteAt(seconds, SIDEBAR_X + 36, y + 25);
        }
    };

    // draw timers
    drawPlayerBlock(10, "DARK", m_darkTime, m_currentTurn == PieceColor::DARK);
    drawPlayerBlock(180, "LIGHT", m_lightTime, m_currentTurn == PieceColor::LIGHT);

    // calculate status
    PieceColor oppCol = (m_currentTurn == PieceColor::LIGHT) ? PieceColor::DARK : PieceColor::LIGHT;
    bool inCheck = m_board.isCheck(oppCol);
    bool canMove = m_board.anyValidMoves(m_currentTurn);

    int statusY = 100;
    LCD.SetFontColor(RED);

    if (inCheck && canMove) {
        LCD.WriteAt("CHECK!", SIDEBAR_X, statusY);
    } else if (inCheck && !canMove) {
        LCD.WriteAt("CHECK", SIDEBAR_X, statusY);
        LCD.WriteAt("MATE!", SIDEBAR_X, statusY + 20);
    } else if (!inCheck && !canMove) {
        LCD.SetFontColor(YELLOW);
        LCD.WriteAt("STALE", SIDEBAR_X, statusY);
        LCD.WriteAt("MATE", SIDEBAR_X, statusY + 20);
    }

    LCD.Update();
    m_wasTouchPressed = m_isTouchPressed;
}
