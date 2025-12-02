/**
 * @file
 * @brief The game screen class
 * @author Carter Russell
 * @date 2025-12-02
 */

#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include "screen/Screen.h"
#include "FEHLCD.h"
#include "chess/Board.h" 
#include "FEHUtility.h" 

enum class GameState {
    AWAITING_SELECTION,
    PIECE_SELECTED
};

class GameScreen : public Screen {
private:
    // initialize board
    Board chessBoard;

    // initialize current state, turn, and position of piece to be selected
    GameState currentState = GameState::AWAITING_SELECTION;
    PieceColor currentTurn = PieceColor::LIGHT;
    int selectedX = -1; // invalid value as a placeholder 
    int selectedY = -1;

    // track if the screen was already pressed on the previous frame
    bool wasTouchPressed = false;
    bool isTouchPressed;
public:
    virtual ScreenType update() override;
    virtual void draw() override; 
};

#endif //GAMESCREEN_H
