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
    // declare variables here
public:
    GameScreen(); // constructor
    virtual ScreenType update() override;
    virtual void draw() override; 
};

#endif //GAMESCREEN_H
