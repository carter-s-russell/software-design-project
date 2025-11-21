#include "chess/King.h"
#include "chess/Board.h"
#include <cmath>

/**
 * @brief The King constructor
 *
 * It uses a ternary operator to handle the image of the King from its color
 * @param color Color of the King 
 */
King::King(PieceColor color)
    : Piece(color, (color == PieceColor::LIGHT) ? "res/king_light.png" : "res/king_dark.png"),
      m_hasMoved(false)
{
    // empty constructor body
}

bool King::isValidMove(int curX, int curY, int toX, int toY, bool checkSafety, Board* board) {
    bool validMove = false;
    bool avoidCheck = !checkSafety; // if we don't check for checks, this will be true

    // pointer to the piece at the target space
    Piece* pieceAtTarget = board->getPieceAt(toX, toY);

    // checks if the king is trying to move to a space within one around it
    // includes the same space, which should be filtered out later
    bool oneSpace = ((std::abs(curX-toX) <= 1) && (std::abs(curY-toY) <= 1));

    // if the king is trying to move to an empty space or a space with an opposite color piece
    if (oneSpace && ((pieceAtTarget == nullptr) || pieceAtTarget->getColor() != m_color)) {
        validMove = true;
    }

    // TODO: add castling
    if (false) {
        validMove = true;
    }

    // make sure move does not cause a check
    if (checkSafety && validMove) {
        avoidCheck = board->avoidsCheck(curX, curY, toX, toY);
    }

    // must be a valid psuedo-move and avoid any checks to be a valid move
    return validMove && avoidCheck;
}

void King::setHasMoved() {
    m_hasMoved = true;
}
