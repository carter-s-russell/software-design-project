#include "screen/GameScreen.h"
#include "FEHLCD.h"

// Constructor Implementation
GameScreen::GameScreen() {
    // Setup logic...
}

ScreenType GameScreen::update() {
    // initialize board
    Board chessBoard;

    // initialize current state, turn, and position of piece to be selected
    GameState currentState = GameState::AWAITING_SELECTION;
    PieceColor currentTurn = PieceColor::LIGHT;
    int selectedX = -1; // invalid value as a placeholder 
    int selectedY = -1;

    // track if the screen was already pressed on the previous frame
    bool wasTouchPressed = false;

    // lambda function for pixel to coordinate
    auto pixelToCoord = [](int pixel) {
        return pixel / SQUARE_SIZE;
    };

    while (true) {
        // checking for user input
        int pixelX, pixelY;

        // current state of the touch
        bool isTouchPressed = LCD.Touch(&pixelX, &pixelY);

        // this now only runs on the frame that the touch happened
        if (isTouchPressed && !wasTouchPressed) {
            int gridX = pixelToCoord(pixelX);
            int gridY = pixelToCoord(pixelY);
            bool validGrid = (gridX >= 0) && (gridX < 8) && (gridY >= 0) && (gridY < 8);

            if ((currentState == GameState::AWAITING_SELECTION) && validGrid) {
                // std::cout << "select: " << gridX << "," << gridY << std::endl;
                Piece* selectedPiece = chessBoard.getPieceAt(gridX, gridY);

                // selects piece if the selected square is a piece of the color of the current turn
                if (selectedPiece != nullptr && selectedPiece->getColor() == currentTurn) {
                    selectedX = gridX;
                    selectedY = gridY;

                    // flip current state
                    currentState = GameState::PIECE_SELECTED;
                }
            } else if ((currentState == GameState::PIECE_SELECTED)) {
                // state must flip no matter what input is given
                currentState = GameState::AWAITING_SELECTION;

                // allows for clicking outside of board to reset current move
                if (validGrid) {
                    // std::cout << "move to: " << gridX << "," << gridY << std::endl;
                    Piece* selectedPiece = chessBoard.getPieceAt(selectedX, selectedY);
                    bool validMove = selectedPiece->isValidMove(selectedX, selectedY, gridX, gridY, true, &chessBoard);
                    // std::cout << "Valid move: " << validMove << std::endl;
                    if (validMove) {
                        chessBoard.move(selectedX, selectedY, gridX, gridY);

                        // flip turn using ternary operator
                        currentTurn = (currentTurn == PieceColor::LIGHT) ? PieceColor::DARK : PieceColor::LIGHT;
                    }
                }
            }
        }

        // sets the background to black
        LCD.Clear(BLACK);

        // draws the board
        chessBoard.draw();

        // check if the available move indicators need to be drawn
        if (currentState == GameState::PIECE_SELECTED) {
            chessBoard.drawAvailableMoves(selectedX, selectedY);
        }

        // temporary code to write turn order to screen
        if (currentTurn == PieceColor::LIGHT) {
            LCD.SetFontColor(WHITE);
            LCD.WriteAt("Turn:", 250, 25);
            LCD.WriteAt("LIGHT", 250, 50);
        } else {
            LCD.SetFontColor(WHITE);
            LCD.WriteAt("Turn:", 250, 25);
            LCD.WriteAt("DARK", 250, 50);
        }

        // temporary code to test for checks
        PieceColor oppCol = (currentTurn == PieceColor::LIGHT) ? PieceColor::DARK : PieceColor::LIGHT;
        if (chessBoard.isCheck(oppCol)) {
            LCD.SetFontColor(WHITE);
            LCD.WriteAt("Check!", 250, 100);
        }

        // updates screen
        LCD.Update();

        // updating frame check
        wasTouchPressed = isTouchPressed;

        // prevents cpu from running at 100%
        Sleep(0.01);
    }
}

void GameScreen::draw() {
    // chessBoard.draw();

    // sets the background to black
    LCD.Clear(BLACK);
    LCD.SetFontColor(WHITE);
    LCD.WriteAt("Game goes here", 100, 25);

}
