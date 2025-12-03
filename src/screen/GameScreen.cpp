#include "screen/GameScreen.h"
#include "FEHLCD.h"

ScreenType GameScreen::update() {
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
    // sets the background to black
    LCD.Clear(BLACK);

    // draws the board
    m_board.draw();

    // check if the available move indicators need to be drawn
    if (m_currentState == GameState::PIECE_SELECTED) {
        m_board.drawAvailableMoves(m_selectedX, m_selectedY);
    }

    // temporary code to write turn order to screen
    if (m_currentTurn == PieceColor::LIGHT) {
        LCD.SetFontColor(WHITE);
        LCD.WriteAt("Turn:", 250, 25);
        LCD.WriteAt("LIGHT", 250, 50);
    } else {
        LCD.SetFontColor(WHITE);
        LCD.WriteAt("Turn:", 250, 25);
        LCD.WriteAt("DARK", 250, 50);
    }

    // temporary code to test for checks
    PieceColor oppCol = (m_currentTurn == PieceColor::LIGHT) ? PieceColor::DARK : PieceColor::LIGHT;
    bool inCheck = m_board.isCheck(oppCol);
    bool canMove = m_board.anyValidMoves(m_currentTurn);
    if (inCheck && canMove) {
        LCD.SetFontColor(WHITE);
        LCD.WriteAt("Check!", 250, 100);
    } else if (inCheck && !canMove) {
        LCD.SetFontColor(WHITE);
        LCD.WriteAt("Check", 250, 100);
        LCD.WriteAt("mate!", 250, 120);
    } else if (!inCheck && !canMove) {
        LCD.SetFontColor(WHITE);
        LCD.WriteAt("Stale", 250, 100);
        LCD.WriteAt("mate..", 250, 120);
    }

    // updates screen
    LCD.Update();

    // updating frame check
    m_wasTouchPressed = m_isTouchPressed;
}
