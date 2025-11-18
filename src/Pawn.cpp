#include "chess/Pawn.h"
#include "FEHLCD.h"

/**
 * @brief The Pawn constructor
 *
 * It uses a ternary operator to handle the image of the Pawn from its color
 * @param color Color of the Pawn 
 */
Pawn::Pawn(PieceColor color) : Piece(color, (color == PieceColor::LIGHT) ? "res/pawn_light.png" : "res/pawn_dark.png") {
    // empty constructor body
}

bool Pawn::isValidMove(int curX, int curY, int toX, int toY) {
    // TODO: add logic
    return true;
}
